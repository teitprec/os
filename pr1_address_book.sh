
#!/bin/bash

file="addressbook.txt"

while true
do
    echo
    echo "===== ADDRESS BOOK ====="
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
                if [ -s "$file" ]; then
                    echo "Name        Phone"
                    echo "----------------------"
                    cat "$file"
                else
                    echo "Address Book is Empty"
                fi
            else
                echo "Address Book does not exist."
            fi
            ;;

        3)
            touch "$file"
            read -p "Enter Name: " name
            read -p "Enter Phone: " phone

            echo "$name $phone" >> "$file"
            echo "Record Inserted Successfully"
            ;;

        4)
            if [ -f "$file" ]; then
                read -p "Enter Name to Delete: " name

                if grep -q "^$name " "$file"; then
                    awk -v n="$name" '$1 != n' "$file" > temp.txt
                    mv temp.txt "$file"
                    echo "Record Deleted Successfully"
                else
                    echo "Record Not Found"
                fi
            else
                echo "Address Book does not exist."
            fi
            ;;

        5)
            if [ -f "$file" ]; then
                read -p "Enter Name to Modify: " oldname

                if grep -q "^$oldname " "$file"; then
                    read -p "Enter New Name: " newname
                    read -p "Enter New Phone: " newphone

                    awk -v old="$oldname" -v new="$newname" -v phone="$newphone" '
                    BEGIN { OFS=" " }
                    $1 == old {
                        $1 = new
                        $2 = phone
                    }
                    { print }
                    ' "$file" > temp.txt

                    mv temp.txt "$file"
                    echo "Record Modified Successfully"
                else
                    echo "Record Not Found"
                fi
            else
                echo "Address Book does not exist."
            fi
            ;;

        6)
            echo "Thank You!"
            echo "Exiting Address Book..."
            exit 0
            ;;

        *)
            echo "Invalid Choice! Try Again."
            ;;
    esac
done
