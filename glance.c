#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define KNRM "\x1B[0m"
#define KCYN "\x1B[36m"
#define KBLU "\x1B[34m"
#define KGRN "\x1B[32m"

int comp(const void *a, const void *b) {

  struct dirent *entA = *(struct dirent **)a;

  struct dirent *entB = *(struct dirent **)b;

  return strcmp(entA->d_name, entB->d_name);
}

int main(int argc, char *argv[]) {

  struct dirent *entry;

  DIR *dp;

  struct dirent **fileList = NULL;

  int cap = 10;

  int count = 0;

  char *path; // = (argc > 1) ? argv[1] : ".";

  bool hidden = false;

  if (argc == 1)
    path = ".";
  if (argc == 2) {
    path = argv[1];
  }
  if (argc == 3) {
    path = argv[1];
    if (strcmp(argv[2], "h") == 0)
      hidden = true;
  }

  dp = opendir(path);

  fileList = malloc(cap * sizeof(struct dirent *));

  if (dp == NULL) {
    perror("Error opening directory");
    return 1;
  }

  while ((entry = readdir(dp)) != NULL) {

    if (count > cap) {
      cap *= 2;
      fileList = realloc(fileList, cap * sizeof(struct dirent *));
    }

    fileList[count] = malloc(sizeof(struct dirent));

    memcpy(fileList[count], entry, sizeof(struct dirent));

    //   printf(KCYN "%s" KNRM "|", fileList[count]->d_name);

    count++;
  }

  closedir(dp);

  qsort(fileList, count, sizeof(struct dirent *), comp);

  for (int i = 0; i < count; i++) {

    if (!hidden && fileList[i]->d_name[0] != '.' &&
        strcmp(fileList[i]->d_name, ".") != 0 &&
        strcmp(fileList[i]->d_name, "..") != 0) {

      char *icon = (fileList[i]->d_type == DT_DIR) ? "📁" : "📄";

      char *color = (fileList[i]->d_type == DT_DIR) ? KBLU : KCYN;

      if (fileList[i]->d_type == DT_DIR) {

        color = KBLU;
      } else {
        color = KCYN;
      }
      if (access(fileList[i]->d_name, X_OK) == 0 &&
          fileList[i]->d_type != DT_DIR) {
        color = KGRN;
        icon = "🔨";
      }

      printf("%s%s%-3s\n", color, icon, fileList[i]->d_name);
    }
    if (hidden) {
      char *icon = (fileList[i]->d_type == DT_DIR) ? "📁" : "📄";

      char *color = (fileList[i]->d_type == DT_DIR) ? KBLU : KCYN;

      printf("%s%s%-3s\n", color, icon, fileList[i]->d_name);
    }

    //    printf(KCYN "%s" KNRM "|", fileList[i]->d_name);

    free(fileList[i]);
  }

  free(fileList);

  return 0;
}
