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
Minimal example - Invoke a model with the random data
"""

import sys
import argparse
from statistics import mean
from ai_runner import AiRunner

_DEFAULT = "serial"


def example(args):

    runner = AiRunner(debug=args.debug)

    if not runner.connect(args.desc):
        return 1

    print(runner, flush=True)

    runner.summary(level=args.verbosity)

    inputs = runner.generate_rnd_inputs(batch_size=args.batch)

    print("Invoking the model with random data (b={})..".format(inputs[0].shape[0]), flush=True)
    _, profile = runner.invoke(inputs)

    print("")
    print("host execution time      : {:.3f}ms".format(profile["debug"]["host_duration"]))
    print("number of samples        : {}".format(len(profile["c_durations"])))
    print("inference time by sample : {:.3f}ms (average)".format(mean(profile["c_durations"])))
    print("")

    runner.disconnect()

    return 0


def main():
    """ script entry point """

    parser = argparse.ArgumentParser(description="Minimal example")

    parser.add_argument(
        "--desc",
        "-d",
        metavar="STR",
        type=str,
        help="description for the connection",
        default=_DEFAULT,
    )
    parser.add_argument(
        "--batch", "-b", metavar="INT", type=int, help="number of sample", default=1
    )
    parser.add_argument("--debug", action="store_true", help="debug option")
    parser.add_argument(
        "--verbosity",
        "-v",
        nargs="?",
        const=1,
        type=int,
        choices=range(0, 3),
        help="set verbosity level",
        default=0,
    )

    args = parser.parse_args()

    return example(args)


if __name__ == "__main__":
    sys.exit(main())
