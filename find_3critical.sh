#!/bin/bash

./nauty/geng -C -d4 $@ | ./is_not_karb.native 2 | ./directg_deg_min_2.native -o | ./is_kcritical.native 3

