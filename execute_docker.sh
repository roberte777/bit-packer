#!/bin/bash
#
docker build -t big-endian . 
docker run --rm -it big-endian 
