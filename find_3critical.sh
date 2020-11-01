#!/bin/bash

geng -C -d4 $@ | parallel --block-size 140 --pipe "directg -o | ./is_kcritical.native 3"

