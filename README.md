# CIS 554 Introduction to C++ @ Syracuse University

# Lectures
* I gave up bring them over from blackboard. What's there is there.

# Assignments
* Assignments 1-7. Some made me lose brain cells and have random variable names as jokes hehe.

# Scripts

## mem_leak.sh
* mem_leak was a script I put together to accept an assignment (or any c++ file), compile using `g++ -std=c++17` and pass the binary into GNU leaks.
* Piping mem_leak.sh to grep returns the line where it shows how many memory leaks your c++ file has.

```sh
$ mem_leaks.sh | grep leaks
```

## submission_header.sh
* submission_header.sh was a script that I created because I was lazy and wanted a "quick" way to add the required header.
  * Would've have taken at most 2 seconds to copy and paste but whatever ... 

![Screenshot 2023-12-14 at 8 45 39 PM](https://github.com/gmaldona/cis-554/assets/60359847/bc19e84e-81e5-4c4f-b91a-dca46d95c09b)

([memé source](https://www.reddit.com/r/ProgrammerHumor/comments/kwlc4e/ah_yes_the_programmer_move/))
