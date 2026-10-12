# RYB-Team-4

## Setup

### 1. Follow the tutorial on connecting the PYNQ board to the internet
https://pynq.tue.nl/general/internet/

### 2. Create a GitHub account (https://github.com)

### 3. Setup the repo on the PYNQ
```
cd libpynq-5EWC0-2023-v0.2.6/applications/
git init
git config --global user.name "<Your Name>"
git config --global user.email "<You Email>"
git add .
git commit -m "Marge commit"
git remote add origin https://github.com/bulviakas/RYB-Team-4.git
git pull origin main
git config pull.rebase false
git pull origin main --allow-unrelated-histories
git config push.default upstream
git push --set-upstream origin master
// You'll probably have to wait until I approve the pull request
git checkout main
```