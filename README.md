# RYB-Team-4

## Setup

### 1. Follow the tutorial on connecting the PYNQ board to the internet
https://pynq.tue.nl/general/internet/

### 2. Create a GitHub account (https://github.com)

### 3. Setup the repo on the PYNQ
```
cd libpynq-5EWC0-2023-v0.2.6/applications/
git init -b main
git remote add origin https://github.com/bulviakas/RYB-Team-4.git
git fetch origin
git reset origin/main
git branch --set-upstream-to=origin/main main
git config pull.rebase true
```
### Average daily workflow after making changes
```
git pull                  # When you start working - get the latest code from everyone
...
git add .
git commit -m "<Description of changes made>"
git pull                  # In case anybody pushed new code during your work
git push
```