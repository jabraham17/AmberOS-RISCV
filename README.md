qemu-system-riscv64 -machine virt -bios build/bin/kernel -serial mon:stdio

qemu-system-riscv64 -machine virt -cpu rv64 -smp 4 -m 128M -drive if=none,format=raw,file=hdd.dsk,id=foo -device virtio-blk-device,scsi=off,drive=foo -nographic -serial mon:stdio -bios none -device virtio-rng-device -device virtio-gpu-device -device virtio-net-device -device virtio-tablet-device -device virtio-keyboard-device -kernel build/bin/kernel

qemu-system-riscv64 -machine virt -cpu rv64 -smp 1 -m 128M -device virtio-keyboard-device -bios none -kernel build/bin/kernel.elf -serial mon:stdio

<!-- # -device virtio-gpu-device -->

qemu-system-riscv64 -machine virt -cpu rv64ima -smp 1 -m 128M \
-device virtio-keyboard-device \
-bios none -kernel build/bin/kernel.elf -serial mon:stdio -gdb tcp::1234 -S

/opt/riscv-ima/bin/riscv64-unknown-elf-gdb build/bin/kernel.elf -ex "target remote :1234"
/opt/riscv-ima/bin/riscv64-unknown-elf-objdump -d build/bin/kernel.elf

# Resources

- https://wiki.osdev.org/RISC-V_Bare_Bones
- https://osblog.stephenmarz.com/

# RISC-V

Summary of the data provided here (https://riscv.org/technical/specifications/).

# Privilege levels

| Encoding | Name       | Abbr |
| -------- | ---------- | ---- |
| `00`       | User       | `U`   |
| `01`       | Supervisor | `S`    |
| `10`       | Reserved   |      |
| `11`       | Machine    | `M`    |

## CSRs

- `satp`
  - supervisor address translation and protection
  - contains root page table and other VM info
- `mepc`
  - machine expection pc
  - stores address of instruction on exception
  - mret uses this value to jump back to executing code
- `mtval`
  - exception-specific information to assist software in handling the trap
- `mtvec`
  - address of trap handler, must be 4 byte aligned
  - lowest 2 bits specify mode, 0 is direct, 1 is vectored
- `mcause`
- `mstatus`
  - machine status
  - `MPP(11)` - privilege mode
  - `MPIE(7)` - machine pending interrupt enable
    - must match `MIE`
  - `MIE(3)` - machine interrupt enable
    - must match `MPIE`
- `mhartid`
  - ID of hardware threat (hart)
- `mie`
  - machine interrupt enable
    - `MSIE(3)` - enable machine software interrupts
    - `MTIE(7)` - enable machine timer interrupts
    - `MEIE(11)` - enable machine external interrupts
- `mscratch`
  - machine scratch register

## Special instructions

- `mret`
  - jumps to `mepc`
  - enables interrupts for the current privilege
  - sets the current privileged level to `MPP`
  - sets `MPP` to `U`.
- `csrw csr, reg`
  - write CSR
- `csrr reg, csr`
  - read CSR
- `csrrw dst, csr, src`
  - place src in csr, read csr into dst

## Traps

- MSB of `mcause` CSR determeines if interrupt or exception
- The rest of `mcause` is the exception code

### Interrupts

| Exception Code | Description                   |
| -------------- | ----------------------------- |
| `0`            | Reserved                      |
| `1`            | Supervisor software interrupt |
| `2`            | Reserved                      |
| `3`            | Machine software interrupt    |
| `4`            | Reserved                      |
| `5`            | Supervisor timer interrupt    |
| `6`            | Reserved                      |
| `7`            | Machine timer interrupt       |
| `8`            | Reserved                      |
| `9`            | Supervisor external interrupt |
| `10`           | Reserved                      |
| `11`           | Machine external interrupt    |
| `12-15`        | Reserved                      |
| `>=16`         | Designated for platform use   |

### Exceptions

| Exception Code | Description                    |
| -------------- | ------------------------------ |
| `0`            | Instruction address misaligned |
| `1`            | Instruction access fault       |
| `2`            | Illegal instruction            |
| `3`            | Breakpoint                     |
| `4`            | Load address misaligned        |
| `5`            | Load access fault              |
| `6`            | Store/AMO address misaligned   |
| `7`            | Store/AMO access fault         |
| `8`            | Environment call from U-mode   |
| `9`            | Environment call from S-mode   |
| `10`           | Reserved                       |
| `11`           | Environment call from M-mode   |
| `12`           | Instruction page fault         |
| `13`           | Load page fault                |
| `14`           | Reserved                       |
| `15`           | Store/AMO page fault           |
| `16-23`        | Reserved                       |
| `24-31`        | Designated for custom use      |
| `32-47`        | Reserved                       |
| `48-63`        | Designated for custom use      |
| `>=64`         | Reserved                       |

# VIRT machine in QEMU

## Memory Map

| Region      | Base Address  | Size          |
| ----------- | ------------- | ------------- |
| `DEBUG`     | `0x0`         | `0x100`       |
| `MROM`      | `0x1000`      | `0x1_1000`    |
| `TEST`      | `0x10_0000`   | `0x1000`      |
| `CLINT`     | `0x200_0000`  | `0x1_0000`    |
| `PLIC`      | `0xc00_0000`  | `0x400_0000`  |
| `UART0`     | `0x1000_0000` | `0x100`       |
| `VIRTIO`    | `0x1000_1000` | `0x1000`      |
| `DRAM`      | `0x8000_0000` | `0x0`         |
| `PCIE_MMIO` | `0x4000_0000` | `0x4000_0000` |
| `PCIE_PIO`  | `0x0300_0000` | `0x0001_0000` |
| `PCIE_ECAM` | `0x3000_0000` | `0x1000_0000` |

## memory mapped registers

| Register   | address      | use                                                                             |
| ---------- | ------------ | ------------------------------------------------------------------------------- |
| `mtime`    | `0x0200bff8` | number of cycles                                                                |
| `mtimecmp` | `0x02004000` | machine timer interrupt is fired<br>when this is greater than or equal to mtime |

## Clock

Clock in QEMU is `10` MHz or `10,000,000` cycles a second.


## UART - NS16550a
