mkdir -p ./floppy
mount -o loop boot.img ./floppy
cp STAGE2.SYS ./floppy
cp KERNEL.SYS ./floppy
sleep 1
umount ./floppy