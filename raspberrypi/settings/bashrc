#!/bin/bash

DIR="/home/student334/cpsc334/"
LOC=$(hostname -I)
filename="ip.md"

echo "$LOC" > "$DIR/$filename"
echo "IP address ($LOC) has been saved to $DIR/$filename"

github_user="lucysun118"
github_repo="cpsc334"
repo_folder="cpsc334/raspberrypi/$filename"

cd "$DIR" || exit
git config user.email "l.sun@yale.edu"
git config user.name "lucysun118"
git add "$filename"
git commit -m "Update IP address" --allow-empty
git push origin main
