file='./build/build.ino'

echo "" > $file
echo '#include <stdlib.h>' >> $file
echo '#include <stdio.h> ' >> $file
echo '#include <stddef.h>' >> $file
echo '#include <stdio.h> ' >> $file
echo '#include <stdint.h>' >> $file

cat src/encoder/lights.c >> $file
cat src/pwm/write_pwm.c >> $file
cat src/motor/motor.c >> $file
cat src/encoder/photo_res.c >> $file
cat src/encoder/speedv2.c >> $file
cat main.c >> $file

arduino-cli compile --fqbn arduino:avr:nano build/
arduino-cli upload -b arduino:avr:nano -p /dev/ttyACM0 build/build.ino
stty -F /dev/ttyACM0 9600 raw -clocal -echo
