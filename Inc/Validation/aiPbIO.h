/*
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 */

/*!
 * \file aiPbIO.h
 * \brief Low Level nano PB stack functions
 */

#ifndef _AI_PB_IO_H_
#define _AI_PB_IO_H_

#include <pb.h>

int pb_io_stream_init(void);

void pb_io_flush_ostream(void);
void pb_io_flush_istream(void);

pb_ostream_t pb_io_ostream(int fd);
pb_istream_t pb_io_istream(int fd);

#endif /* _AI_PB_IO_H_ */

