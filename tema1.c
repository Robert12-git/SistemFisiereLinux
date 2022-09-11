#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300
#define HOME "home"

struct Dir;
struct File;

typedef struct Dir{
	char *name;
	struct Dir* parent;
	struct File* head_children_files;
	struct Dir* head_children_dirs;
	struct Dir* next;
} Dir;

typedef struct File {
	char *name;
	struct Dir* parent;
	struct File* next;
} File;

// Init file with all variables null
void initFile (File *file, char *name, Dir *parent) {
	file->name = (char *) calloc (strlen (name) + 1, sizeof (char));
	if (!(file->name)) {
		printf ("Unable to allocate memory for name of file\n");
		return;
	}
	strcpy (file->name, name);
	file->parent = parent;
	file->next = NULL;
}

// Init directory with all variables null
void initDir (Dir *directory, char *name, Dir *parent) {
	directory->name = (char *) calloc (strlen (name) + 1, sizeof (char));
	if (!(directory->name)) {
		printf ("Unable to allocate memory for name of directory\n");
		return;
	}
	strcpy (directory->name, name);
	directory->parent = parent;
	directory->head_children_files = NULL;
	directory->head_children_dirs = NULL;
	directory->next = NULL;
}

// Create home directory in order to have initial directory
Dir *homeDir () {
	// Alloc memory for home directory and check if allocation was ok
	Dir *home = NULL;
	
	home = (Dir *) malloc (sizeof (Dir));
	if (!home) {
		printf ("Unable to allocate home directory\n");
		return NULL;
	}

	char *homeName = NULL;

	homeName = (char *) calloc (strlen (HOME) + 1, sizeof (char));
	if (!homeName) {
		printf ("Unable to allocate memory for home name directory\n");
		return NULL;
	}
	strcpy (homeName, HOME);

	// Initialize home directory
	initDir (home, homeName, NULL);
	free (homeName);

	return home;
}

// Free memory for home directory at the end of program
void deleteDir (Dir *homeDir) {
	File *headFile = homeDir->head_children_files;
	for (File *poz = headFile; poz != NULL;) {
		File *aux = poz;
		poz = poz->next;
		free (aux->name);
		free (aux);
	}

	Dir *headDir = homeDir->head_children_dirs;
	for (Dir *poz = headDir; poz != NULL;) {
		Dir *aux = poz->next;
		deleteDir (poz);
		poz = aux;
	}
	
	free (homeDir->name);
	free (homeDir);
}

// Search for staff with same name
int searchName (Dir *parent, char *name) {
	// Check if there is any directory with same name as object we want to create
	Dir *dirList = parent->head_children_dirs;

	for (Dir *currDir = dirList; currDir != NULL; currDir = currDir->next)
		if (strcmp (currDir->name, name) == 0)
			return -1;

	// Check if there is any file with same name as object we want to create
	File *fileList = parent->head_children_files;

	for (File *currFile = fileList; currFile != NULL; currFile = currFile->next)
		if (strcmp (currFile->name, name) == 0)
			return -2;


	return 1;
}

// Add file to file list
int addFile (Dir *parent, char *name) {
	// Create the new file
	File *file = NULL;

	file = (File *) malloc (sizeof (File));
	if (!file) {
		printf ("Unable to allocate memory for new file\n");
		return -1;
	}
	initFile (file, name, parent);

	// Check if there are other files in directory
	if (!(parent->head_children_files)) {
		// If there aren't new file is head file for fileList
		parent->head_children_files = file;
	} else {
		// If there are other files, insert alphabetically
		File *head = parent->head_children_files, *preFile = NULL;
		
		for (File *currFile = head; currFile != NULL; currFile = currFile->next) {
			if (strcmp (currFile->name, file->name) > 0 && preFile == NULL) {
				file->next = currFile;
				parent->head_children_files = file;
				break;
			} else if (strcmp (currFile->name, file->name) < 0 &&
											currFile->next == NULL) {
				currFile->next = file;
				break;
			} else if (strcmp (currFile->name, file->name) > 0 &&
								strcmp (preFile->name, file->name) < 0) {
				preFile->next = file;
				file->next = currFile;
				break;
			}

			preFile = currFile;
		}
	}

	return 1;
}

// Create file in current directory
void touch (Dir* parent, char* name) {
	int flag;
	flag = searchName (parent, name);
	if (flag > 0) {
		flag = addFile (parent, name);
		if (flag < 0)
			return;
	} else {
		printf ("File already exists\n");
	}
}

// Add directory to directoryList
int addDir (Dir *parent, char *name) {
	// Create the new directory
	Dir *dir = NULL;

	dir = (Dir *) malloc (sizeof (Dir));
	if (!dir) {
		printf ("Unable to allocate memory for new directory\n");
		return -1;
	}
	initDir (dir, name, parent);

	// Check if there are other directories in directory
	if (!(parent->head_children_dirs)) {
		// If there aren't, new directory is head directory for directoryList
		parent->head_children_dirs = dir;
	} else {
		// If there are other directories, insert alphabetically
		Dir *head = parent->head_children_dirs, *preDir = NULL;
		
		for (Dir *currDir = head; currDir != NULL; currDir = currDir->next) {
			if (strcmp (currDir->name, dir->name) > 0 && preDir == NULL) {
				dir->next = currDir;
				parent->head_children_dirs = dir;
				break;
			} else if (strcmp (currDir->name, dir->name) < 0 &&
											currDir->next == NULL) {
				currDir->next = dir;
				break;
			} else if (strcmp (currDir->name, dir->name) > 0 &&
								strcmp (preDir->name, dir->name) < 0) {
				preDir->next = dir;
				dir->next = currDir;
				break;
			}

			preDir = currDir;
		}
	}

	return 1;
}

// Create directory in current directory
void mkdir (Dir* parent, char* name) {
	int flag;

	flag = searchName (parent, name);
	if (flag > 0) {
		flag = addDir (parent, name);
		if (flag < 0)
			return;
	} else {
		printf ("Directory already exists\n");
	}
}

// Show everything that is in the directory
void ls (Dir* parent) {
	Dir *headDir = parent->head_children_dirs;
	
	for (Dir *currDir = headDir; currDir != NULL; currDir = currDir->next)
		printf ("%s\n", currDir->name);
	
	File *headFile = parent->head_children_files;

	for (File *currFile = headFile; currFile != NULL; currFile = currFile->next)
		printf ("%s\n", currFile->name);
}

// Remove file
void rm (Dir* parent, char* name) {
	File *head = parent->head_children_files, *prevFile = NULL;
	int flag = -1;

	for (File *currFile = head; currFile != NULL; currFile = currFile->next) {
		if (strcmp (currFile->name, name) == 0) {
			File *toDelete = currFile;

			if (!prevFile)
				parent->head_children_files = parent->head_children_files->next;
			else
				prevFile->next = currFile->next;

			free (toDelete->name);
			free (toDelete);
			flag = 1;
			break;
		}
		prevFile = currFile;
	}

	if (flag < 0)
		printf ("Could not find the file\n");
}

// Recursively remove directory
void rmdir (Dir* parent, char* name) {
	Dir *head = parent->head_children_dirs, *preDir = NULL;
	int flag = -1;

	for (Dir *currDir = head; currDir != NULL; currDir = currDir->next) {
		if (strcmp (currDir->name, name) == 0) {
			Dir *toDelete = currDir;
			if (!preDir)
				parent->head_children_dirs = parent->head_children_dirs->next;
			else
				preDir->next = currDir->next;
			deleteDir (toDelete);
			flag = 1;
			break;
		}
		preDir = currDir;
	}

	if (flag < 0)
		printf ("Could not find the dir\n");
}

// Change directory where it's needed
void cd(Dir** target, char *name) {
	if (strcmp (name, "..") == 0) {
		if ((*target)->parent)
			*target = (*target)->parent;
		return;
	} else {
		Dir *head = (*target)->head_children_dirs;

		for (Dir *currDir = head; currDir != NULL; currDir = currDir->next)
			if (strcmp (currDir->name, name) == 0) {
				(*target) = currDir;
				return;
			}
	}

	printf ("No directories found!\n");
}

// Utilitary function to implement recursively pwd
void pwdUtils (Dir *target, char *path, int *length) {
	if (target->parent)
		pwdUtils (target->parent, path, length);
	*length += sprintf (path + *length, "/%s", target->name);
}

// Show path to current directory
char *pwd (Dir* target) {
	char *path = NULL;
	int length = 0;

	path = (char *) calloc (MAX_INPUT_LINE_SIZE, sizeof (char));
	if (!path) {
		printf ("Unable to allocate memory for path string\n");
		return NULL;
	}

	pwdUtils (target, path, &length);
	return path;
}

// Free memory before end of program
void stop (Dir* target) {
	deleteDir (target);
	return;
}

// Show as a tree all files and directories recursively from current dir
void tree (Dir* target, int level) {
	Dir *headDir = target->head_children_dirs;
	for (Dir *currDir = headDir; currDir != NULL; currDir = currDir->next) {
		for (int i = 0; i < level * 4; i++)
			printf (" ");
		printf ("%s\n", currDir->name);
		tree (currDir, level + 1);
	}

	File *headFile = target->head_children_files;
	for (File *currFile = headFile; currFile != NULL; currFile = currFile->next) {
		for (int i = 0; i < level * 4; i++)
			printf (" ");
		printf ("%s\n", currFile->name);
	}
}

// Decide if working with file or directory
int fileOrDir (Dir *parent, char *name) {
	Dir *headDir = parent->head_children_dirs;
	for (Dir *currDir = headDir; currDir != NULL; currDir = currDir->next)
		if (strcmp (currDir->name, name) == 0)
			return 1;
	
	File *headFile = parent->head_children_files;
	for (File *currFile = headFile; currFile != NULL; currFile = currFile->next)
		if (strcmp (currFile->name, name) == 0)
			return 2;

	return 0;
}

/*
	 Return address to file or directory to look forrward, type var used
	 to identify type of file
*/ 
void *findObject (int *type, char *name, Dir *parent) {
	*type = fileOrDir (parent, name);
	if (*type == 1) {
		Dir *headDir = parent->head_children_dirs;
		for (Dir *currDir = headDir; currDir != NULL; currDir = currDir->next)
			if (strcmp (currDir->name, name) == 0)
				return currDir;
	} else if (*type == 2) {
		File *headFile = parent->head_children_files;
		for (File *currFile = headFile; currFile != NULL; currFile = currFile->next)
			if (strcmp (currFile->name, name) == 0)
				return currFile;	
	} else
		return NULL;
}

/* 
	Find old file or directory,  copy info of old object, eliminate old object
	and add new object in needed list
*/
void mv(Dir* parent, char *oldname, char *newname) {
	int flag = searchName (parent, oldname);
	if (flag > 0) {
		printf ("File/Director not found\n");
		return;
	}

	flag = searchName (parent, newname);
	if (flag < 0) {
		printf ("File/Director already exists\n");
		return;
	}

	if (fileOrDir (parent, oldname) == 1) {
		int type;
		Dir *oldDir, *newDir, *preDir = NULL;

		oldDir = findObject (&type, oldname, parent);
		mkdir (parent, newname);
		newDir = findObject (&type, newname, parent);
		newDir->head_children_dirs = oldDir->head_children_dirs;
		newDir->head_children_files = oldDir->head_children_files;
		
		for (Dir *currDir = parent->head_children_dirs;
						currDir != NULL; currDir = currDir->next) {
			if (currDir == oldDir) {
				if (!preDir)
					parent->head_children_dirs = parent->head_children_dirs->next;
				else {
					preDir->next = currDir->next;
				}
			}
			preDir = currDir;
		}

		free (oldDir->name);
		free (oldDir);

	} else if (fileOrDir (parent, oldname) == 2) {
		rm (parent, oldname);
		touch (parent, newname);
	} else if (fileOrDir (parent, oldname) == 0)
		return;
}

int main () {
	// Create home directory to start program
	Dir *home = NULL;
	home = homeDir ();
	if (!home) {
		printf ("No home directory\n");
		exit (-1);
	}
	
	// Set current directory as home directory at the beginning
	Dir *current = home;

	// Alloc memory for buffer and declare max size of buffer for getline func
	char *buffer = NULL;
	size_t size = MAX_INPUT_LINE_SIZE;

	buffer = (char *)calloc (MAX_INPUT_LINE_SIZE, sizeof (char));

	// Stop program if allocation failed
	if (!buffer) {
		printf ("Unable to allocate buffer\n");
		exit (-2);
	}

	do {
		/*
		Summary:
			Reads from stdin a string and breaks it down into command and in
			case it needs into a name.
		*/

		// Read input
		getline (&buffer, &size, stdin);

		char *token = NULL;
		token = strtok (buffer, " \n");
		if (strcmp (token, "touch") == 0) {
			token = strtok (NULL, " \n");
			touch (current, token);
		} else if (strcmp (token, "mkdir") == 0) {
			token = strtok (NULL, " \n");
			mkdir (current, token);
		} else if (strcmp (token, "ls") == 0) {
			ls (current);
		}  else if (strcmp (token, "rm") == 0) {
			token = strtok (NULL, " \n");
			rm (current, token);
		} else if (strcmp (token, "rmdir") == 0) {
			token = strtok (NULL, " \n");
			rmdir (current, token);
		} else if (strcmp (token, "cd") == 0) {
			token = strtok (NULL, " \n");
			cd (&current, token);
		} else if (strcmp (token, "tree") == 0) {
			tree (current, 0);
		} else if (strcmp (token, "pwd") == 0) {
			char *path = NULL;
			path = pwd (current);
			if (!path) {
				printf ("Unable to locate path\n");
				exit (-3);
			}
			printf ("%s\n", path);
			free (path);
		} else if (strcmp (token, "mv") == 0) {
			token = strtok (NULL, " \n");
			char *token1 = strtok (NULL, " \n");
			mv (current, token, token1);
		}
		 else if (strcmp (token, "stop") == 0) {
			 stop (home);
			 free (buffer);
			 break;
		 }
			
	} while (/*condition*/1);

	return 0;
}