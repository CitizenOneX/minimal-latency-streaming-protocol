/*
 * MLSP Minimal Latency Streaming Protocol - Client usage example
 * Based on https://github.com/bmegli/minimal-latency-streaming-protocol/blob/master/README.md
 * Copyright 2019-2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "../mlsp.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int error;
	struct mlsp* streamer;
	struct mlsp_config streamer_config = { "127.0.0.1", 9766, 500 }; //connect to localhost, port, 500 ms timeout

	uint32_t frame_size = 320 * 240 * sizeof(uint8_t);
	uint8_t* frame_data = (uint8_t*)malloc((size_t)frame_size);

	streamer = mlsp_init_client(&streamer_config);
	if (streamer == NULL)
	{
		fprintf(stderr, "Error initializing client\n");
		return -1;
	}
	else
	{
		fprintf(stderr, "Client initialized successfully\n");
	}

	struct mlsp_frame network_frame = { 0 };
	int i = 1;
	while (1)
	{
		//...
		//prepare your data in some way
		//...
		network_frame.data = frame_data;
		network_frame.size = frame_size;

		error = mlsp_send(streamer, &network_frame, 0);
		if (error != MLSP_OK)
		{
			fprintf(stderr, "Error sending frame: %d\n", error);
			break;
		}
		else
		{
			if (i % 1000 == 0) fprintf(stderr, "Frame %d sent, size=%d\n", i, network_frame.size);
		}

		i++;
	}

	mlsp_close(streamer);

	free(frame_data);
}