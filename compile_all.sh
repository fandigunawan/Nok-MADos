#!/bin/bash

DIALOG=${DIALOG=tools/dialog.exe}
BANNER="MADos - The free OS for N* handsets"

done_box () {
    echo
    echo "###################################################"
    echo "#                                                 #"
    echo "#                      DONE                       #"
    echo "#                                                 #"
    echo "###################################################"
    exit;
}

g3n0lite_compile () {
    if [ -f virgin.fls ]; then
        echo "# * creating a 'clean' nokia.fls from virgin.fls"	 >> log
        cp virgin.fls nokia.fls >/dev/null 2>&1;
        msg=`tools/g3n0lite.exe -f nokia.fls -s tools/MADos_startup.gsc 2>&1`;
        export RC=$?;
        if [ "x$RC" != "x1" ]; then
		echo $msg >> err.$$;
    		exit;
        fi;
        ID=`echo -e "$msg" | grep MADos_startup | gawk "{printf \\$3;}"`
        echo "# * use the 5E0 ID   0x${ID}   to call mados via menu! (not automatically done)"	 >> log
    	echo "# * reserving ${CODESIZE} bytes in CODE chunk.."	 >> log
        msg=`tools/g3n0lite.exe -f nokia.fls -i ${CODESIZE} 2>&1`;
        export RC=$?;
        if [ "x$RC" != "x1" ]; then
		echo $msg >> err.$$;
    		exit;
        fi;
        EMBED=1;
    else
        echo >> log
        echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!">> log
    	echo "!                                                 !">> log
        echo "!               - NO virgin.fls -                 !">> log
        echo "!                                                 !">> log
    	echo "!        place the file 'embed.fls' at CODE       !">> log
        echo "!          section in PPM (g3n0lite v2.0)         !">> log
        echo "!                                                 !">> log
    	echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!">> log
        EMBED=0;
    fi;
}


. compile.conf

echo > log

# overwriting TYPE if argument is set
if [ $1 ]; then
    export TYPE=$1;
fi;

if [ "x$TYPE" != "xBEAUTY" ] && [ "x$TYPE" != "xPC" ]; then
    export PHONE_STR=" - ${PHONE}";
else
    export PHONE_STR="";
fi;


if [ "x$TYPE" != "xBEAUTY" ] && [ "x$TYPE" != "xSTANDALONE" ] && [ "x$TYPE" != "xEMBED" ] && [ "x$TYPE" != "xFULLEMBED" ] && [ "x$TYPE" != "xLOADER" ] && [ "x$TYPE" != "xPC" ]; then
    clear
    echo "###################################################"
    echo "#                                                 #"
    echo "#          no valid TYPE selected                 #"
    echo "#                                                 #"
    echo "###################################################"
    done_box;
fi;

# BEAUTIFYING
if [ "x$TYPE" == "xBEAUTY" ]; then
(
#    clear
#    echo "###################################################"
#    echo "#                                                 #"
#    echo "#          beautyfying the code                   #"
#    echo "#                                                 #"
#    echo "###################################################"
    num=0;
    cnt=0;
    
    echo "XXX";
    echo "0";
    echo "\n  Counting files";
    echo "XXX";
    S_FILES=`find ./ -name *.s`;
    C_FILES=`find ./ -name *.c`;
    H_FILES=`find ./ -name *.h`;

    for file in $C_FILES; do
	let num=$num+1;
#	num=`echo $num + 1 | bc`;
    done
    for file in $S_FILES; do
	let num=$num+1;
#	num=`echo $num + 1 | bc`;
    done
    for file in $H_FILES; do
	let num=$num+1;
#	num=`echo $num + 1 | bc`;
    done
    
    for file in $S_FILES; do
	let cnt=$cnt+1;
	let pct=100*$cnt/$num;
#	cnt=`echo $cnt + 1 | bc`;
#	pct=`echo "100 * $cnt / $num" | bc`;
	echo "XXX";
	echo "$pct";
	echo "\n  Beautyfying  <$file>";
	echo "XXX";
        chmod u+rw $file > /dev/null 2>&1
        unix2dos $file > /dev/null 2>&1;
        dos2unix $file > /dev/null 2>&1;
    done;
    for file in $C_FILES; do
	let cnt=$cnt+1;
	let pct=100*$cnt/$num;
#	cnt=`echo $cnt + 1 | bc`;
#	pct=`echo "100 * $cnt / $num" | bc`;
	echo "XXX";
	echo "$pct";
	echo "\n  Beautyfying  <$file>";
	echo "XXX";
        chmod u+rw $file > /dev/null 2>&1
        unix2dos $file > /dev/null 2>&1;
        dos2unix $file > /dev/null 2>&1;
        indent -i4 -sc -bli0 -cs -prs -cdb -bl0 -cbi0 -cli4 -ss -nut -ts4 -l200 -bap $file > /dev/null  2>&1;
    done;
    for file in $H_FILES; do
	let cnt=$cnt+1;
	let pct=100*$cnt/$num;
#	cnt=`echo $cnt + 1 | bc`;
#	pct=`echo "100 * $cnt / $num" | bc`;
	echo "XXX";
	echo "$pct";
	echo "\n  Beautyfying  <$file>";
	echo "XXX";
        chmod u+rw $file > /dev/null 2>&1
        unix2dos $file > /dev/null 2>&1;
        dos2unix $file > /dev/null 2>&1;
        indent -i4 -sc -bli0 -cs -prs -cdb -bl0 -cbi0 -cli4 -ss -nut -ts4 -l200 -bap $file;
    done;
) | $DIALOG --backtitle "$BANNER" --title "Beautyfying" --guage "Initializing" 8 70 0
exit;
fi;

(

echo "XXX";
echo "0";
echo "\n  Preparing file lists";
echo "XXX";

# SET PATH
if [ ! $ARM_COMPILER_PATH ] && [ "x$TYPE" != "xPC" ]; then
    # Set the ARM_COMPILER_PATH and ARM_COMPILER_PREFIX only when
    # the user hasn't set them themselves
    if [ "x$MACHTYPE" == "xi686-pc-cygwin" ]; then
        export ARM_COMPILER_PATH="/home/g3gg0/gccarm/arm-thumb-elf/bin";
    else
        export ARM_COMPILER_PATH="/gcc-arm/arm-thumb-elf/bin/";
    fi
    export ARM_COMPILER_PREFIX=""
fi
if [ "x$TYPE" == "xPC" ]; then
    export COMPILER_PATH="/bin";
    #export mode_str="          P C            ";
    export mode_str="PC";
else
    export COMPILER_PATH="$ARM_COMPILER_PATH";
    export COMPILER_PREFIX="$ARM_COMPILER_PREFIX";
fi


# EXPORT LISTS
if [ "x$TYPE" != "xFULLEMBED" ]; then
    export type="$TYPE";
else
    export type="STANDALONE";
    #export mode_str="    F U L L  E M B E D   ";
    export mode_str="FULLEMBED";
    export suffix="_embed";
fi

export C_EXCL_GREP="none_existing/no_one_create_this"
export O_EXCL_GREP="none_existing/no_one_create_this"

# this part should be improved ... didn't get it work
#for file in $C_EXCL_${type}; do
#        export C_EXCL_GREP="$C_EXCL_GREP\|$file";
#    done;
#    for file in $O_EXCL_${type}; do
#        export O_EXCL_GREP="$O_EXCL_GREP\|$file";
#    done;
#    export O="$O_${type}";
#done;

# if upper part is improved, the following can be removed
if [ "x$type" == "xSTANDALONE" ]; then
    for file in $C_EXCL_STANDALONE; do
        export C_EXCL_GREP="$C_EXCL_GREP\|$file";
    done;
    for file in $O_EXCL_STANDALONE; do
        export O_EXCL_GREP="$O_EXCL_GREP\|$file";
    done;
    export O="$O_STANDALONE";
elif [ "x$type" == "xEMBED" ]; then
    for file in $C_EXCL_EMBED; do
        export C_EXCL_GREP="$C_EXCL_GREP\|$file";
    done;
    for file in $O_EXCL_EMBED; do
        export O_EXCL_GREP="$O_EXCL_GREP\|$file";
    done;
    export O="$O_EMBED";
elif [ "x$type" == "xLOADER" ]; then
    for file in $C_EXCL_LOADER; do
        export C_EXCL_GREP="$C_EXCL_GREP\|$file";
    done;
    for file in $O_EXCL_LOADER; do
        export O_EXCL_GREP="$O_EXCL_GREP\|$file";
    done;
    export O="$O_LOADER";
elif [ "x$type" == "xPC" ]; then
    for file in $C_EXCL_PC; do
        export C_EXCL_GREP="$C_EXCL_GREP\|$file";
    done;
    for file in $O_EXCL_PC; do
        export O_EXCL_GREP="$O_EXCL_GREP\|$file";
    done;
    export O="$O_PC";
fi;

export C_FILES="";
for file in $C_FILES_ALL; do
	if [ -e "$file.c" ]; then
		export C_FILES="${C_FILES}`echo $file | grep -v "$C_EXCL_GREP"` "
	fi;
done;

export O_FILES="";
export O_FILES_ALL_GREP="none_existing/no_one_create_this.o";
for file in $O_FILES_ALL; do
    export O_FILES="${O_FILES}`echo $file | grep -v "$O_EXCL_GREP"` "
    export O_FILES_ALL_GREP="$O_FILES_ALL_GREP\|${file}.o"
done;

export O_LIST="";
for file in $O_FILES; do
    export O_LIST="${file}.o $O_LIST";
done;


# SET REMAINING mode_str
if [ "x$TYPE" == "xSTANDALONE" ]; then
    #export mode_str="   S T A N D A L O N E   ";
    export mode_str="STANDALONE";
    export suffix="";
    export TARGET="ARM";
fi;
if [ "x$TYPE" == "xLOADER" ]; then
    #export mode_str="        L O A D E R      ";
    export mode_str="LOADER";
    export suffix="_loader";
    export TARGET="ARM";
fi;
if [ "x$TYPE" == "xEMBED" ]; then
    #export mode_str="         E M B E D       ";
    export mode_str="EMBED";
    export suffix="_embed";
    export TARGET="ARM";
fi;
if [ "x$TYPE" == "xPC" ]; then
    #export mode_str="         E M B E D       ";
    export mode_str="PC";
    export suffix="_pc";
    export TARGET="PC";
fi;

#clear
#echo "###################################################"
#echo "#                                                 #"
#echo "#             Compiling project MADos             #"
#echo "#                                                 #"
#echo "#            $mode_str            #"
#echo "#                                                 #"
#echo "###################################################"



if [ "x$TYPE" != "xPC" ]; then
#    echo 
#    echo "###################################################"
#    echo "#                                                 #"
#    echo "#          generating MAD flash header            #"
#    echo "#        and standard initialization code         #"
#    echo "#                                                 #"
#    echo "###################################################"
    echo "XXX";
    echo "0";
    echo "\n  Generating MAD initialisation code";
    echo "XXX";
    msg=`${COMPILER_PATH}/${COMPILER_PREFIX}as --defsym PHONE_${PHONE}=1 -mthumb-interwork -EB -mbig-endian -mcpu=arm7tdmi core/crt0${suffix}.s -o core/crt0.o;`
fi;

#echo 
#echo "###################################################"
#echo "#                                                 #"
#echo "#           compiling C code objects              #"
#echo "#                                                 #"
#echo "###################################################"



num=0;
pct=0;
cnt=0;
warn="";


echo "XXX";
echo "0";
echo "\n  Counting files";
echo "XXX";

for file in $C_FILES; do
    let num=$num+1;
done

for file in $C_FILES; do

    if [ -f ${file}.c ]; then
    let cnt=$cnt+1;
    let pct=50*$cnt/$num;
    mode="thumb";
    if [ "x`echo $file | gawk -F\+ \"{ print \\$2; }\"`" != "x" ]; then
        mode="`echo $file | gawk -F\+ \"{ print \\$2; }\"`";
        file="`echo $file | gawk -F\+ \"{ print \\$1; }\"`";
    fi;
    echo "XXX";
    echo "$pct";
    echo "\n  Compiling  <$file.c> ($mode)";
    echo "XXX";
    if [ "x$TYPE" != "xPC" ]; then
	msg=`${COMPILER_PATH}/${COMPILER_PREFIX}gcc    -m$mode           $O -nostartfiles -fno-builtin-vsnprintf -mbig-endian -mcpu=arm7tdmi -c $file.c -o $file.o $DEFINES 2>&1`;
    else
        msg=`gcc  $O  -c $file.c -o $file.o  $DEFINES  2>&1`;
    fi;
    
    for object in $O_FILES_ALL; do
	if [ "x$object" == "x${file}_${TARGET}" ]; then
	    mv $file.o ${file}_${TARGET}.o;
	fi;
    done;
    
    RC=$?;
    
    if [ "x$RC" != "x0" ]; then
	echo -ne "$msg" >> err.$$;
	exit;
    fi;
    if [ "x$msg" != "x" ]; then
	warn=`echo "$warn\n$file:\n$msg"`
    fi;
    fi;
done
if [ "x$warn" != "x" ]; then
    echo "$warn" >> warn.$$;
fi;


    echo "XXX";
    echo "50";
    echo "\n  Collecting Objects";
    echo "XXX";

    for file in $C_FILES; do
	skip="no";
	
	# split filename from options
	if [ "x`echo $file | gawk -F\+ \"{ print \\$2; }\"`" != "x" ]; then
	    file=`echo $file | gawk -F\+ "{ print \\$1; }"`;
	fi;
	
	# is the file some private developer file?
	for object in $O_FILES_ALL; do
	    if [ "x${object}" == "x${file}_${TARGET}" ]; then
		skip="yes";
	    fi
	done;
	
	# then dont link the plain .o file since it doesnt exist
	if [ "x$skip" != "xyes" ]; then
	    export O_LIST="$O_LIST ${file}.o"
	fi;
    done

    echo "XXX";
    echo "55";
    echo "\n  Linking Objects";
    echo "XXX";

    if [ "x$TYPE" == "xPC" ]; then
	msg=`gcc $O $O_LIST -o test.exe 2>&1`
    else
	cp core/crt0.o .
	msg=`${COMPILER_PATH}/${COMPILER_PREFIX}gcc     -mthumb           $O -nodefaultlibs -nostartfiles -mbig-endian -Wl,-EB -Wa,-EB -Xlinker data/${PHONE}/memmap${suffix} -mcpu=arm7tdmi $O_LIST -o flash.o 2>&1`
    fi;
    RC=$?;

    if [ "x$RC" != "x0" ]; then
	echo -ne "$msg" | grep -v interwork > err.$$;
	exit 1;
    fi;

    if [ "x$TYPE" != "xPC" ]; then
	rm crt0.o
	echo "XXX";
	echo "58";
	echo "\n  Dumping";
	echo "XXX";
	${COMPILER_PATH}/${COMPILER_PREFIX}objcopy -Obinary flash.o ${TYPE}.fls
    fi;


    if [ "x$TYPE" == "xSTANDALONE" ]; then
	echo "XXX";
	echo "60";
	echo "\n  Resizing";
	echo "XXX";
	OLDSIZE=`ls -o ${TYPE}.fls | gawk "{printf \\$4;}"`;
	let SIZE=65536-${OLDSIZE}%65536;
	dd if=/dev/zero of=${TYPE}.fls obs=${OLDSIZE} seek=1 ibs=${SIZE} count=1 > /dev/null 2>&1;
    fi

    echo "XXX";
    echo "70";
    echo "\n  Cleanup";
    echo "XXX";

    find -name \*~    | xargs rm >/dev/null 2>&1
    find -name \*.o   | grep -v "$O_FILES_ALL_GREP" | xargs rm >/dev/null 2>&1
    find -name \*.bin | xargs rm >/dev/null 2>&1
    
    if [ "x$TYPE" != "xPC" ]; then
	chmod -x ${TYPE}.fls
    else
	chmod +x test.exe
    fi;

if [ "x$TYPE" != "xFULLEMBED" ] && [ "x$TYPE" != "xEMBED" ]; then
	echo "XXX";
	echo "100";
	echo "\n  Done";
	echo "XXX";    
else

	echo "XXX";
	echo "75";
	echo "\n  Embedding";
	echo "XXX";
    MADSIZE=`ls -o ${TYPE}.fls | gawk "{printf \\$4;}"`;
    let CODESIZE=${MADSIZE}+10000;

    if [ ! -f nokia.fls ]; then    
	g3n0lite_compile;
    fi;
    
    if [ -f nokia.fls ]; then    
        CODECHUNK=0;
        NOKSIZE=`ls -o nokia.fls | gawk "{printf \\$4;}"`;
        echo "# * we will need ${MADSIZE} bytes.." >> log	
        if [ ${NOKSIZE} -eq 1900544 ]; then
    	    CODECHUNK=1310784;
    	    echo "# * merging into 2MB Flash"	>> log
        fi;
        if [ ${NOKSIZE} -eq 3473408 ]; then
    	    CODECHUNK=2687040;
	    echo "# * merging into 4MB Flash (not tested)"	 >> log
        fi;
        if [ ${CODECHUNK} -eq 0 ]; then
            mv ${TYPE}.fls embedflash.fls   > /dev/null 2>&1;
    	    echo >> log
            echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" >> log
    	    echo "!                                                 !" >> log
            echo "!             - WRONG nokia.fls -                 !" >> log
    	    echo "!                                                 !" >> log
            echo "!        place the file 'embed.fls' at CODE       !" >> log
    	    echo "!          section in PPM (g3n0lite v2.0)         !" >> log
            echo "!                                                 !" >> log
    	    echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" >> log
        else
	    let POS=${MADSIZE}+${CODECHUNK};
            dd if=nokia.fls skip=1 bs=${CODECHUNK} 2>/dev/null | dd of=deleteme1 count=1 bs=${MADSIZE}  > /dev/null 2>&1;
    	    gunzip -c data/0xFF.gz > deleteme2>/dev/null
	    dd if=deleteme of=deleteme2 bs=${MADSIZE} count=1  > /dev/null 2>&1;
    	    diff deleteme1 deleteme2 >/dev/null 2>&1;
    	    export RC=$?;
    	    if [ "x$RC" != "x0" ]; then
        	    dd if=nokia.fls of=deleteme1 bs=1 skip=${CODECHUNK} count=4  > /dev/null 2>&1;
	            echo "CODE" > deleteme2
	            diff deleteme1 deleteme2 >/dev/null 2>&1;
        	    export RC=$?;
	            if [ "x$RC" != "x0" ]; then
#        	    	echo >> log1
#            		echo "###################################################" >> log1
#            		echo "#                                                 #" >> log1
#            		echo "#          GOT AN INVALID NOKIA.FLS (no CODE)     #" >> log1
#            		echo "#                                                 #" >> log1
#            		echo "###################################################" >> log1
                    g3n0lite_compile;
            else
#            		echo >> log1
#            		echo "###################################################" >> log1
#            		echo "#                                                 #" >> log1
#            		echo "#          NOT ENOUGH FREE SPACE IN CODE          #" >> log1
#        	    	echo "#                                                 #" >> log1
#        		echo "#            - creating new nokia.fls -           #" >> log1
#            		echo "#                                                 #" >> log1
#            		echo "###################################################" >> log1
	        	g3n0lite_compile;
                fi;
            else
	        EMBED=1;
    	    fi;
    	    if [ ${EMBED} -eq 1 ]; then
    	        echo "# * enough space free in CODE chunk" >> log
	        cp nokia.fls embedflash.fls  > /dev/null 2>&1;
    	        dd if=${TYPE}.fls of=embedflash.fls obs=${CODECHUNK} seek=1  > /dev/null 2>&1;
    	        dd if=nokia.fls of=embedflash.fls ibs=${POS} skip=1 seek=1 obs=${POS}  > /dev/null 2>&1;
    	        rm ${TYPE}.fls  > /dev/null 2>&1;
		tools/g3n0lite -f embedflash.fls -c > /dev/null 2>&1
    	        mv embedflash.fls ${TYPE}.fls  > /dev/null 2>&1;
	        echo "# * EMBEDDED" >> log
       	    fi;
        fi;   
    else
        mv flash.fls ${TYPE}.fls   > /dev/null 2>&1;
        echo >> log
        echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" >> log
        echo "!                                                 !" >> log
        echo "!            - missing nokia.fls -                !" >> log
        echo "!                                                 !" >> log
        echo "!        place the file 'embed.fls' at CODE       !" >> log
        echo "!          section in PPM (g3n0lite v2.0)         !" >> log
        echo "!                                                 !" >> log
        echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" >> log
    fi
    rm deleteme* >/dev/null 2>&1
	echo "XXX";
	echo "100";
	echo "\n  Done";
	echo "XXX";
fi;

) | $DIALOG --backtitle "$BANNER" --title "Compiling - ${TYPE}${PHONE_STR}" --guage "Initializing" 8 70 0

#
# removed $mode_str since its a private variable of the above subshell i extended
# maybe move assignment of this variable outside the subshell?
#
#   - g3gg0 -
#

if [ -f warn.$$ ]; then
    msg=`cat warn.$$`;
    if [ "x$LEAVELOG" != "xYES" ]; then
        rm warn.$$;
    fi;
    $DIALOG --backtitle "$BANNER" --title "Compiling - ${TYPE}${PHONE_STR}" --msgbox "Compile Warnings:\n\n$msg" 20 70 
fi;

if [ -f err.$$ ]; then
    msg=`cat err.$$`;
    if [ "x$LEAVELOG" != "xYES" ]; then
	rm err.$$;
    fi;
    $DIALOG --backtitle "$BANNER" --title "Compiling - ${TYPE}${PHONE_STR}" --msgbox "Compile Error:\n\n$msg" 20 70 
    rm log > /dev/null 2>&1
    exit;
fi;

msg=`cat log`;
$DIALOG --backtitle "$BANNER" --title "Finished" --msgbox "MADos (${TYPE}${PHONE_STR}) is Ready...\n\n$msg" 20 70 

rm log > /dev/null 2>&1


