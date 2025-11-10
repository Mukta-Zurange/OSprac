#!/bin/bash

# Address Book File
address_book="addressbook.txt"

# Menu Driven Program
while true
do
    echo "=============================="
    echo " Address Book Menu "
    echo "=============================="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert a Record"
    echo "4. Delete a Record"
    echo "5. Modify a Record"
    echo "6. Exit"
    echo -n "Enter your choice: "
    read choice

    case $choice in
        1)
            touch $address_book
            echo "Address Book created successfully."
            ;;
        2)
            if [ -s $address_book ]; then
                echo "------ Address Book ------"
                cat $address_book
            else
                echo "Address Book is empty."
            fi
            ;;
        3)
            echo -n "Enter Name: "
            read name
            echo -n "Enter Phone: "
            read phone
            echo -n "Enter Email: "
            read email
            echo "$name | $phone | $email" >> $address_book
            echo "Record inserted successfully."
            ;;
        4)
            echo -n "Enter Name to delete: "
            read dname
            if grep -q "$dname" $address_book; then
                grep -v "$dname" $address_book > temp.txt && mv temp.txt $address_book
                echo "Record deleted successfully."
            else
                echo "Record not found."
            fi
            ;;
        5)
            echo -n "Enter Name to modify: "
            read mname
            if grep -q "$mname" $address_book; then
                echo -n "Enter New Name: "
                read newname
                echo -n "Enter New Phone: "
                read newphone
                echo -n "Enter New Email: "
                read newemail
                sed -i "s/$mname.*/$newname | $newphone | $newemail/" $address_book
                echo "Record modified successfully."
            else
                echo "Record not found."
            fi
            ;;
        6)
            echo "Exiting Program. Goodbye!"
            exit 0
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac
done
