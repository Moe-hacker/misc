#!/data/data/com.termux/files/usr/bin/bash
ls|while read music
do
zip -9 $music.zip $music
done
