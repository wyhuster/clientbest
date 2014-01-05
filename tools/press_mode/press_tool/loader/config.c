#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "config.h"

#define MAX_VAR_NUM (16)
#define MAX_VAR_NAME_LEN (128)
#define MAX_VAR_VALUE_LEN MAX_PATH_LEN
#define COMMENT_CHARACTER '#'
#define LINE_SIZE (768)

static char ga_variables[MAX_VAR_NUM][MAX_VAR_NAME_LEN + 1];
static char ga_values[MAX_VAR_NUM][MAX_VAR_VALUE_LEN + 1];
static int g_var_num = 0;

static void get_dir_path_of_file(char *file, char *dir_path)
{
	char *temp;
	strncpy(dir_path, file,  MAX_PATH_LEN);
	temp = strrchr(dir_path,'/');
	temp[0] = '\0';
}

static void remove_trailing_chars(char *path, char c)
{
	size_t len;
	len = strlen(path);
	while (len > 0 && path[len-1] == c)
		path[--len] = '\0';
}

static int get_key(char **line,char **key,char **value)
{ 
	char *linepos;
	char *temp;
	linepos = *line;
	if (!linepos)
		return -1;

	/* skip whitespace */ 
	while (isspace(linepos[0]))
		linepos++;

	if (linepos[0] == '\0')
	{
		return -1;
	}
	

	*key = linepos;
	while (1) { 
		linepos++;
		if (linepos[0] == '\0')

			{return -1;}
		if (isspace(linepos[0]))
			break;
		if (linepos[0] == '=')
			break;

	}


	linepos[0] = '\0';

	while (1) { 
		linepos++;
		if (linepos[0] == '\0')
		{
			return -1;
		}

		if (isspace(linepos[0]))

			continue;
		if (linepos[0] == '=')
			continue;
		break;
	}

	if (linepos[0] == '"')
		{	
			linepos++;
		}

		else 
		{ 
			return -1;
		} 
	*value = linepos;
	
	temp = strchr(linepos, '"');
	if (!temp)
	{
		return -1;
	}
	temp[0] = '\0';
	return 0;
}

int parse_config_file(char *path_to_config_file)
{
	char line[LINE_SIZE + 2];
	char *bufline;
	char *linepos;
	char *variable;
	char *value;char *buf;
	size_t bufsize;size_t cur;
	size_t count;
	int lineno;
	int retval = 0;

	FILE *cfg_file = fopen(path_to_config_file,"r");
	if (NULL == cfg_file)
	{ 
		printf("cant open '%s' as config file.\n", path_to_config_file);
        g_var_num = -1;
		goto EXIT;
	}	

	/* loop through the whole file */ 
	lineno = 0;cur = 0;
	while (NULL != fgets(line,sizeof(line),cfg_file))
	{ 
		lineno++;
		bufline = line;
		count = strlen(line);

		if (count > LINE_SIZE)
		{
			printf ("line too long,conf line skipped %s,line %d",path_to_config_file,lineno);
			continue;
		}

		while ((count > 0) && isspace(bufline[0]))
			{ 
				bufline ++;
				count --;
			}
		if(count == 0)
			continue;

		if (bufline[0] == COMMENT_CHARACTER)
			continue;

		memcpy(line, bufline, count);
		line[count] = '\0';

		linepos = line;
		retval = get_key(&linepos,&variable,&value);
		if (retval != 0){ 
			printf("error parsing %s, line %d:%d.\n",path_to_config_file,lineno, (int)(linepos-line));
			continue;
		}
		if (g_var_num >= MAX_VAR_NUM)
		{
			printf("too many vars in %s, line %d:%d.\n", path_to_config_file, lineno, (int)(linepos-line));
			continue;
		}



		if (strlen(variable) > MAX_VAR_NAME_LEN)
		{	
			printf("var name to long %s, line %d", path_to_config_file,lineno,(int)(linepos -line));
			continue;
		}

		if (strlen(value) > MAX_VAR_VALUE_LEN)
		{
			printf("value to long %s, line %d: %d.\n",path_to_config_file,lineno, (int)(linepos-line));
			continue;
		}
		strncpy(ga_variables[g_var_num],variable, sizeof(ga_variables[g_var_num]));
		remove_trailing_chars(value, '/');
		strncpy(ga_values[g_var_num],value, sizeof(ga_variables[g_var_num]));
		g_var_num++;
		continue;

}
	fclose(cfg_file);
EXIT:
	return g_var_num;
}

char * get_config_var(char *var_name)
{ 
	int i;
	for(i = 0; i < g_var_num; i++)
	{	
		if (strcasecmp(ga_variables[i], var_name) == 0)

		{return ga_values[i];}

	}
	printf("get %s failed",var_name);
	return NULL;
}
void print_all_vars(void)
{ 
	int i;
	printf("g_var_num == %d\n",g_var_num);
	for(i = 0; i < g_var_num; i++)
	{
		printf("%s = %s\n", ga_variables[i], ga_values[i]);

	}

}

