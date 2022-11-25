#!/data/data/com.termux/files/usr/bin/bash
ls *.mp3|while read music
do
artist=${music%% -*}
name=${music##*-\ }
name=${name%%.mp3}
name=${name%%"（"*}
name=${name%%"("*}
mv "$music" "$name-[$artist].mp3"
done
