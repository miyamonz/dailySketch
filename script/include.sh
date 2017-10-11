#bin/sh
ls src/sketches/ | grep "/" -v | sed -E "s/^(.*)$/#include \"&\"/"
