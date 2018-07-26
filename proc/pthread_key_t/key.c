

pthread_key_t key;
pthread_once_t once = PTHREAD_ONCE_INITIALIZER;

void dest(void *buf)
{
	free(buf);
}

void key_create()
{
	pthread_key_create(key,dest);
}