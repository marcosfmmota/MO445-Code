# Script to generate a file of random kernel banks with norm 1

from random import gauss

def generate_kernel_bank(filename="rand-kernel-bank.txt", nbands=1, kwidth=3, kheight=3, nkernels=8):

    kbank = []
    dim = kwidth*kheight
    for i in range(nkernels):
        kernel = [gauss(0, 1) for i in range(dim)]
        mag = sum(x**2 for x in kernel) ** .5
        kernel = [x/mag for x in kernel]
        bias = gauss(0,1)
        kernel.append(bias)
        kbank.append(kernel)

    with open(filename, "w") as f:
        f.write("{} {} {} {}\n".format(nbands, kwidth, kheight, nkernels))
        for k in kbank:
            for x in k:
                f.write("{} ".format(x))
            f.write("\n")


if __name__ == "__main__":
    generate_kernel_bank()
