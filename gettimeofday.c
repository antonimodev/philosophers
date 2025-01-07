#include <sys/time.h>
#include <stdio.h>

int	main(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    printf("Segundos: %ld\n", tv.tv_sec);
    printf("Microsegundos: %ld\n", tv.tv_usec);

    return 0;
}
