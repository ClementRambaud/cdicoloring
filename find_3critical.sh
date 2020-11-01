#!/bin/bash

geng -C -d4 $@ | parallel -N10 --pipe "directg -o | ./is_kcritical.native 3"

