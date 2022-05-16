#!/usr/bin/env python3

#
# @attention
#
# Copyright (c) 2022 STMicroelectronics.
# All rights reserved.
#
# This software is licensed under terms that can be found in the LICENSE file
# in the root directory of this software component.
# If no LICENSE file comes with this software, it is provided AS-IS.
#

"""
Typical script to the test dataset and specific metric
(i.e. sklearn classification metric) to evaluate the generated model
with the MNIST data set.
"""

import os
import argparse
from statistics import mean
import logging
import numpy as np

from sklearn.metrics import classification_report

os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"
logging.getLogger("tensorflow").setLevel(logging.ERROR)

from tensorflow import keras

from ai_runner import AiRunner

_DEFAULT = "serial"


H, W, C = 28, 28, 1
IN_SHAPE = (H, W, C)
NB_CLASSES = 10


def load_data_test():
    """Load MNIST data set """
    mnist = keras.datasets.mnist
    (_, _), (x_test, y_test) = mnist.load_data()

    # Normalize the input image so that each pixel value is between 0 to 1.
    x_test = x_test / 255.0
    x_test = x_test.reshape(x_test.shape[0], H, W, C).astype(np.float32)

    # convert class vectors to binary class matrices
    y_test = keras.utils.to_categorical(y_test, NB_CLASSES)

    return x_test, y_test


parser = argparse.ArgumentParser(description="Test model")
parser.add_argument("--desc", "-d", metavar="STR", type=str, default=_DEFAULT)
parser.add_argument("--batch", "-b", metavar="INT", type=int, default=None)
args = parser.parse_args()

print('using "{}"'.format(args.desc))
runner = AiRunner()

if not runner.connect(args.desc):
    print('runtime "{}" is not connected'.format(args.desc))
    exit(1)

print(runner, flush=True)
runner.summary()


# Load the data
inputs, refs = load_data_test()

if not "machine" in runner.get_info()["device"]:
    nb = 100 if not args.batch else args.batch
    print(
        "INFO: use only the first {} samples (instead {})".format(nb, inputs.shape[0]), flush=True
    )
    inputs = inputs[:nb]
    refs = refs[:nb]

# Perform the inference
predictions, profile = runner.invoke(inputs)

# Display profiling info
print("")
print("execution time           : {:.3f}s".format(profile["debug"]["host_duration"] / 1000))
print("number of samples        : {}".format(len(profile["c_durations"])))
print("inference time by sample : {:.3f}ms (average)".format(mean(profile["c_durations"])))

# classification report
print("\nClassification report (sklearn.metrics)\n")

# align the shape of the outputs (c-model is always - (b, h, w, c))
predictions[0] = predictions[0].reshape(refs.shape)

target_names = ["c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9"]
print(
    classification_report(
        np.argmax(refs, axis=1), np.argmax(predictions[0], axis=1), target_names=target_names
    )
)

runner.disconnect()
