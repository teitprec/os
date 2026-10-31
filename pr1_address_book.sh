#!/bin/bash

file="addressbook.txt"

while true
do
    echo
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    read -p "Enter choice: " ch

    case "$ch" in
        1)
            touch "$file"
            echo "Address Book Created"
            ;;
        2)
            if [ -f "$file" ]; then
                cat "$file"
            else
                echo "Address Book does not exist. Create it first."
            fi
            ;;
        3)
            touch "$file"
            read -p "Enter Name: " name
            read -p "Enter Phone: " phone
            echo "$name $phone" >> "$file"
            echo "Record Inserted"
            ;;
        4)
            if [ -f "$file" ]; then
                read -p "Enter Name to Delete: " name
                grep -v "^$name " "$file" > temp.txt
                mv temp.txt "$file"
                echo "Record Deleted"
            else
                echo "Address Book does not exist."
            fi
            ;;
       5)
    read -p "Enter name of record to modify: " oldname

    if grep -q "^$oldname " "$file"; then
        read -p "Enter new name: " newname
        read -p "Enter new phone: " newphone

        sed -i "s/^$oldname .*/$newname $newphone/" "$file"
        echo "Record modified"
    else
        echo "Record not found"
    fi
    ;;
        6)
            echo "Exit"
            exit 0
            ;;
        *)
            echo "Invalid Choice"
            ;;
    esac
done
