#include "image.h"
#include "potushop.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    int ret;

    ret = load_bitmap("data/grayscale_expected.bmp");
    assert(ret);
    normalize_pixels();

    {
        ret = load_bitmap("data/sneakers_1024.bmp");
        assert(ret);

        normalize_pixels();

        to_grayscale();

        ret = save_bitmap("grayscale.bmp");
        assert(ret);

        assert(compare_bitmap("data/grayscale_expected.bmp") == 0);
    }


    printf("No prob\n");

    return 0;
}