#!/bin/bash

pick="pickg -d2: -u2: -C"
main="./is_kcritical.native 3"

geng -C -d4 $@ | \
  tee  >(awk 'NR % 4 == 0' | directg -o | $main) \
       >(awk 'NR % 4 == 1' | directg -o | $main) \
       >(awk 'NR % 4 == 2' | directg -o | $main) \
       >(awk 'NR % 4 == 3' | directg -o | $main) \
       > /dev/null
