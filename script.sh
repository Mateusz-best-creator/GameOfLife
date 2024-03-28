#!/bin/bash

echo "Enter commit message: "
read Message
echo "Enter branch name: "
read BranchName

# In this script we prompt user for commit message, branch name and push changes to remote repository
git status
git add .
git status
git commit -m "${Message}"
git push origin ${BranchName}