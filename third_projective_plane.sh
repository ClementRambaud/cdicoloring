# This script shows that any triangulation of order 12 and 13
# and minimum degree at least 6 has vertex-arboricity at most 3

echo "If there exists any counter example, it will be written to stdout:"
echo

echo "test of the 2037 triangulations of order 12 and minimum degree at least 6:"
time surftri -n -m6 12 3 -g | ./is_not_karb.native 3 

echo "test of the 4574 triangulations of order 13 and minimum degree at least 6:"
time surftri -n -m6 13 3 -g | ./is_not_karb.native 3

