cls

SET PATH=c:\z88dk199c;c:\z88dk199c\bin;c:\z88dk199c\lib\;c:\z88dk199c\lib\clibs;c:\z88dk199c\lib\config



@rem zcc +zx -vn -m -o -startup=31 -clib=new main.c

@rem zcc +zx -lndos -create-app -o hello main.c


@rem zcc +zx -lm -m -create-app -startup=1 -clib=new  main.c -o output

@ rem zcc +zx -vn -m -startup=31 -clib=new ramALL.o -o compiled -pragma-include:zpragma.inc @ramlow.lst





@ rem original working compile
@ rem zcc +zx -m -create-app -startup=1 -clib=new  main.c -o output

@rem zcc +zx -m -create-app -startup=1 -clib=new  @ramMAIN.lst -pragma-include:zpragma.inc  -o output


rem compile enemy loctions and create an object file

rem ----------------------------------------------------------------------------------------------------------
zcc +zx -v -c -clib=new --fsigned-char -o objects.o @enemyList.lst

rem exit /b

zcc +zx -m  -startup=1 -clib=new objects.o @ramMAIN.lst -pragma-include:zpragma.inc  -o output

rem ----------------------------------------------------------------------------------------------------------

rem exit /b
rem pause


move "output_CODE.bin" basic
move "output_UNASSIGNED.bin" basic
move "output_UNCONTENDED_enemy_locations.bin" basic
cd basic


appmake +zx -b output_CODE.bin -o code.tap --org 32768 --noloader --blockname code

appmake +zx -b output_UNCONTENDED_enemy_locations.bin -o data.tap --org 63488 --noloader --blockname edata





cd utils
	copy "bas2tap.exe" "..\"
cd ..

	bas2tap -a10 -sBASIC loader.bas basloader.tap


@rem del output_CODE.bin
@rem del output_UNCONTENDED_enemy_locations.bin
@rem del output_UNASSIGNED.bin

copy /b basloader.tap + code.tap + data.tap 1output.tap


move "1output.tap" "..\"

del "basloader.tap"
del "code.tap"
del "data.tap"

cd ..

call beep.bat