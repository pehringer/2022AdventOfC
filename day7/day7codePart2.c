#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	long size;
	int is_dir;
	int visted;
	int num_child;
	char name[32];
	int parent_idx;
	int child_idx[256];
};

int dfs_sum(int node_idx, struct node *nodes) {
	printf("DFS AT %s %s\n", nodes[node_idx].is_dir?"DIR":"FILE", nodes[node_idx].name);
	if(nodes[node_idx].is_dir) {
		for(int idx = 0; idx < nodes[node_idx].num_child; idx++) {;
			nodes[node_idx].size += dfs_sum(nodes[node_idx].child_idx[idx], nodes);
		}
	}
	return nodes[node_idx].size;
}

void main()
{
	// State for file reading.
	FILE* ptr;
	char lines[1024][64];
	int len_lines[1024];
	int num_lines = 0;
	int length = 0;
	char ch;
	// Read in file lines.
	ptr = fopen("day7input.txt", "r");
	if (NULL == ptr) {
		printf("ERROR cannot open day7input.txt\n");
		return;
	}
	while((ch = fgetc(ptr)) != EOF) {
		if(ch == '\n') {
			lines[num_lines][length] = '\0';
			len_lines[num_lines++] = length;
			length = 0;
			continue;
		}
		lines[num_lines][length++] = ch;
	}
	fclose(ptr);
	printf("Number of lines: %d\n", num_lines);


	// State for creating graph.
	struct node nodes[1024];
	int num_nodes = 0;
	int cur_line = 0;
	int node_idx = 0;
	// Manually convert first command (root dir).
	nodes[num_nodes].size = 0;
	nodes[num_nodes].is_dir = 1;
	nodes[num_nodes].visted = 0;
	nodes[num_nodes].num_child = 0;
	memcpy(nodes[num_nodes].name, "/\0", 2);
	nodes[num_nodes++].parent_idx = -1;
	printf("0\tCD / CREATED\n");
	node_idx = 0;
	cur_line++;

	// Process commands.
	while(cur_line < num_lines) {
		// cd command.
		if(lines[cur_line][2] == 'c') {
			// Back dir.
			if(lines[cur_line][5] == '.') {
				node_idx = nodes[node_idx].parent_idx;
				printf("%d\tCD ..\n", cur_line);
			}
			// Root dir.
			else if(lines[cur_line][5] == '/') {
				node_idx = 0;
				printf("%d\tCD /\n", cur_line);
			}
			// Forward dir.
			else {
				// Find existing dir.
				for(int n = 0; n < nodes[node_idx].num_child; n++) {
					int child_idx = nodes[node_idx].child_idx[n];
					if(0 == strcmp(&lines[cur_line][5], nodes[child_idx].name)) {
						node_idx = child_idx;
						printf("%d\tCD %s EXISTING\n", cur_line, nodes[child_idx].name);
						break;
					}
				}
			}
			cur_line++;
		}
		// ls commands. Add each list item to current dir is not present.
		else if(lines[cur_line][2] == 'l') {
			printf("%d\tLS\n", cur_line);
			cur_line++;
			// Keep adding items until next command is found.
			while(cur_line < num_lines && lines[cur_line][0] != '$') {
				if(lines[cur_line][0] == 'd') {
					// No existing dir. Create new dir.
					nodes[num_nodes].size = 0;
					nodes[num_nodes].is_dir = 1;
					nodes[num_nodes].visted = 0;
					nodes[num_nodes].num_child = 0;
					memcpy(nodes[num_nodes].name, &lines[cur_line][4], len_lines[cur_line]-3);
					printf("%d\t  dir %s added.\n", cur_line, nodes[num_nodes].name);
					nodes[num_nodes].parent_idx = node_idx;
					nodes[node_idx].child_idx[nodes[node_idx].num_child++] = num_nodes++;
				}
				else {
					// Get space index. Get file size chars.
					char digits[32];
					int space_idx = 0;
					while(lines[cur_line][space_idx] != ' ') {
						digits[space_idx] = lines[cur_line][space_idx];
						space_idx++;
					}
					digits[space_idx] = '\0';
					// No existing file. Create new file.
					nodes[num_nodes].size = atoi(digits);
					nodes[num_nodes].is_dir = 0;
					nodes[num_nodes].visted = 0;
					nodes[num_nodes].num_child = 0;
					memcpy(nodes[num_nodes].name, &lines[cur_line][space_idx+1], len_lines[cur_line]-space_idx);
					printf("%d\t  file %s added.\n", cur_line, nodes[num_nodes].name);
					nodes[num_nodes].parent_idx = node_idx;
					nodes[node_idx].child_idx[nodes[node_idx].num_child++] = num_nodes++;
				}
				cur_line++;
			}
		}
	}


	// Use dfs for calc dir sums
	dfs_sum(0, nodes);

	// Sum up dirs of at most 100000 in size.
	long sum = 0;
	for(int n = 0; n < num_nodes; n++)
		if(nodes[n].is_dir && nodes[n].size <= 100000)
			sum += nodes[n].size;

	printf("Sum of dirs of at most 100000 in size: %ld\n", sum);

	long current_free = 70000000 - nodes[0].size;
	long space_needed = 30000000 - current_free;
	printf("Space neeed: %ld\n", space_needed);

	long closest_match = nodes[0].size;
	for(int n = 0; n < num_nodes; n++) {
                if(nodes[n].is_dir) {
			long extra_space = nodes[n].size - space_needed;
			if(extra_space >= 0 && extra_space < closest_match)
				closest_match = nodes[n].size;
		}
	}

	printf("Smallest dir to delete for update: %ld\n", closest_match);
}



