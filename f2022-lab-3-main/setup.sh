#! /bin/bash

ROOT_DIR=$(readlink -f `dirname $0`)

cd "$ROOT_DIR"
code .
make launch_fvp &
