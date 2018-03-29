#include <stdlib.h>

#include "client_thread.h"

int
main(int argc, char *argv[])
{
	if (argc < 5) {
		fprintf(stderr, "Usage: %s <port-nb> <nb-clients> <nb-requests> <resources>...\n", argv[0]);
		exit(1);
	}

	port_number = atoi(argv[1]);
	int num_clients = atoi(argv[2]);
	num_request_per_client = atoi(argv[3]);
	num_resources = argc - 4;

	provisioned_resources = malloc(num_resources * sizeof(int));
	for (unsigned int i = 0; i < num_resources; i++)
		provisioned_resources[i] = atoi(argv[i + 4]);

	initializeServer();

	printf("\n\nSERVER INITIALIZED\n\n");

	client_thread *client_threads
		= malloc(num_clients * sizeof(client_thread));
	printf("\n\nclient flag 1\n\n");
	for (unsigned int i = 0; i < num_clients; i++) {
		printf("\n\nclient flag 2\n\n");
		ct_init(&(client_threads[i]));
	}

  for (unsigned int i = 0; i < num_clients; i++) {
    ct_create_and_start (&(client_threads[i]));
  }

  ct_wait_server (client_threads, num_clients);

  // Affiche le journal.
  st_print_results (stdout, true);
  FILE *fp = fopen("client.log", "w");
  if (fp == NULL) {
    fprintf(stderr, "Could not print log");
    return EXIT_FAILURE;
  }
  st_print_results (fp, false);
  fclose(fp);

  free(client_threads);
	free(provisioned_resources);
	
  return EXIT_SUCCESS;
}
