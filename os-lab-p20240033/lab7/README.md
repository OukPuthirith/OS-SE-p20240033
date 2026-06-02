# Lab 7 Questions

## 1. Why did `warmup` fail before you added execute permission?

The `warmup` script failed because it did not have the execute (`x`) permission set. Linux only allows files marked as executable to be run as programs. After using `chmod +x warmup`, the script became executable and could run successfully.

## 2. What does adding `~/bin` to `PATH` allow you to do?

Adding `~/bin` to the `PATH` allows the shell to automatically search for executable files in that directory. This means scripts such as `warmup`, `broadcaster`, `harvester`, and `mailman` can be run by typing their names directly instead of using `./scriptname` or specifying the full path.

## 3. Why does `chmod 733 public_inbox` allow classmates to drop files but not list the inbox?

Permission `733` gives the owner full access (`rwx`) and gives everyone else write and execute permissions (`wx`) without read permission. The write permission allows classmates to create files in the directory, while the lack of read permission prevents them from listing or viewing its contents.

## 4. Why does Linux ignore SUID on shell scripts, and why did we use a compiled C program instead?

Linux ignores SUID on shell scripts because it can create security vulnerabilities, such as race-condition attacks and privilege escalation. A compiled C program is used instead because the operating system can safely apply the SUID bit to a binary executable, allowing it to run with the owner's privileges.

## 5. What is the difference between `>` and `>>` in Bash redirection?

The `>` operator creates a new file or overwrites the contents of an existing file. The `>>` operator appends new output to the end of a file without removing its existing contents.

## 6. How did your `harvester` avoid reading files that were missing or not readable?

The `harvester` script used conditional tests before reading each file. It checked whether the file existed with `[ -f "$target_file" ]` and whether it was readable with `[ -r "$target_file" ]`. Only files that passed both tests were processed.

## 7. What permission problems did you or your classmates need to fix during the lab?

Several permission issues had to be fixed during the lab. Common problems included scripts that were not executable until `chmod +x` was used, inbox directories with incorrect permissions that prevented classmates from writing files, outbox files that were not readable by others, and home directories that required execute permission so classmates could access shared resources. These issues were resolved by applying the correct `chmod` settings.
