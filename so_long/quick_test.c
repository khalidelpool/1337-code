#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int main()
{
    void *mlx = mlx_init();
    mlx_destroy_display(mlx);
    free(mlx);
}