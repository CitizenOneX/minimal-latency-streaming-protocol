/*
 * MLSP Minimal Latency Streaming Protocol - Server usage example
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

int main(int argc, char* argv[])
{
	int error;
	struct mlsp* streamer;
	struct mlsp_config streamer_config = { NULL, 9766 }; //host (NULL=>ANY/0.0.0.0), port

	streamer = mlsp_init_server(&streamer_config);
	if (streamer == NULL)
	{
		fprintf(stderr, "Error initializing server\n");
		return -1;
	}
	else
	{
		fprintf(stderr, "Server initialized successfully\n");
	}

	//here we will be getting data
	const struct mlsp_frame* streamer_frame;
	int i = 1;
	while (1)
	{
		streamer_frame = mlsp_receive(streamer, &error);

		if (streamer_frame == NULL)
		{
			fprintf(stderr, "Error receiving frame: %d\n", error);

			if (error == MLSP_TIMEOUT)
				continue;
			break; //error
		}
		else
		{
			if (i % 1000 == 0) fprintf(stderr, "Frame %d received, size=%d\n", i, streamer_frame->size);
		}

		//...
		//do something with the streamer_frame
		//the ownership remains with library so consume or copy
		//...
		i++;
	}

	mlsp_close(streamer);
}