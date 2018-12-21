#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
//This function is for Step 1
void step1_helper(char * input_name, struct stat sb, char * mode) {
  if (S_ISLNK(sb.st_mode)) {
    char linktarget[256] = {'\0'};
    readlink(input_name, linktarget, 256);
    printf("  File: ‘%s’ -> ‘%s’\n", input_name, linktarget);
  }
  else {
    printf("  File: %s\n", input_name);
  }
  printf(
      "  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu ", sb.st_size, sb.st_blocks, sb.st_blksize);
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      printf("block special file\n");
      mode[0] = 'b';  //Use mode[0] to record types of input
      break;
    case S_IFCHR:
      printf("character special file\n");
      mode[0] = 'c';
      break;
    case S_IFDIR:
      printf("directory\n");
      mode[0] = 'd';
      break;
    case S_IFIFO:
      printf("fifo\n");
      mode[0] = 'p';
      break;
    case S_IFLNK:
      printf("symbolic link\n");
      mode[0] = 'l';
      break;
    case S_IFREG:
      printf("regular file\n");
      mode[0] = '-';
      break;
    case S_IFSOCK:
      printf("socket\n");
      mode[0] = 's';
      break;
    default:
      printf("unknown?\n");
      break;
  }
  //deal with situation that input is character or block file
  if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink);
  }
}
//This function is for Step 2
void step2_helper(struct stat sb, char * mode) {
  unsigned int S_array[9] = {
      S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
  char label[9] = {'r', 'w', 'x', 'r', 'w', 'x', 'r', 'w', 'x'};
  //use for loop to decide element of mode[10]
  for (size_t i = 1; i < 10; i++) {
    if (sb.st_mode & S_array[i - 1]) {
      mode[i] = label[i - 1];
    }
    else {
      mode[i] = '-';
    }
  }
  struct passwd * passwd_stru = getpwuid(sb.st_uid);
  struct group * group_stru = getgrgid(sb.st_gid);
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         sb.st_mode & ~S_IFMT,
         mode,
         sb.st_uid,
         passwd_stru->pw_name,
         sb.st_gid,
         group_stru->gr_name);
}
//this function is for step 4
void step4_helper(struct stat sb) {
  char * atimestr = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  char * mtimestr = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  char * ctimestr = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  printf("Access: %s\n", atimestr);
  printf("Modify: %s\n", mtimestr);
  printf("Change: %s\n", ctimestr);
  printf(" Birth: -\n");
  free(atimestr);
  free(mtimestr);
  free(ctimestr);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    fprintf(stderr, "Usage: inappropriate input !\n");
    exit(EXIT_FAILURE);
  }  //need at least one input argument
  //use for loop deal with each input
  for (int i = 1; i < argc; i++) {
    struct stat sb;
    if (lstat(argv[i], &sb) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }

    char mode[10] = {'\0'};  //remeber mode for step2
    step1_helper(argv[i], sb, mode);
    step2_helper(sb, mode);
    step4_helper(sb);
  }

  return EXIT_SUCCESS;
}
