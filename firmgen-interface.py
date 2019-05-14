import firmware
import sys
from os import listdir
from os.path import isfile, join, abspath
import ctypes

img_arr = None
image_count = None


def format_firmware():
    firmware.DLPC350_Frmw_SPLASH_InitBuffer(image_count)

    new_img = None
    new_img_size = None

    # Uncompressed images
    compression = firmware.SPLASH_UNCOMPRESSED

    for i in range(0, image_count):
        comp_size = None

        imgfile = open(img_arr[i], 'rb').read()
        imgptr = ctypes.cast(imgfile, ctypes.POINTER(ctypes.c_byte))
        imgptr_full = ctypes.cast(imgptr, ctypes.POINTER(ctypes.c_ubyte))

        #ret = firmware.DLPC350_Frmw_SPLASH_AddSplash(imgptr_full, compression, comp_size)

    firmware.DLPC350_Frmw_Get_NewFlashImage(new_img, new_img_size)

    with open("output.bin", 'wb') as f:
        f.write(new_img)
    f.close()

    return


def main():
    global img_arr, image_count
    folder_dir = sys.argv[1]

    print("Firmware build beginning...")

    # Finding image files
    img_arr = [join(folder_dir,f) for f in listdir(folder_dir) if isfile(join(folder_dir, f)) and f.endswith(".bmp")]
    image_count = len(img_arr)

    format_firmware()
    print("Firmware build complete")


if __name__ == "__main__":
    main()