#!/bin/bash

# testing.sh
# 
# Jonathan Metzger
#  Spring 2018
#
# Project for CS4513 Distributed Computing Systems
#

# partition path other than current directory
partition_path="/media/sf_projects/Dumpster-Diving/dumpster"
#partition_path="/media/sf_CS4513/dumpster_copy"

# get the size of the test file.
filesize_dumpster=$(stat -c%s "$partition_path")

#################################################

echo "----------------------------------"
echo "Welcome to Dumpster Diving TESTING"
echo "Created by Jonathan Metzger"
echo "{ rm, dv and dump } tool Utility"
echo "----------------------------------"

#################################################

echo "[ Partition:	$partition_path ]"
echo "[ Size: 	$filesize_dumpster bytes ]"
echo "----------------------------------"

# create 20 versions of test file and time them.
echo "> [ Making 20 test files ]"
for i in {1..20}
	do
		sync
		init=$(date +%s%3N)
		#echo "hello "> "test$i.txt"
		cp test.txt "test$i.txt"
		sync
		final=$(date +%s%3N)
		delta=$((final-init))
		total=$((total + delta))
	done
echo "20 files added in $total milliseconds"
echo "----------------------------------"

# remove 20 test files and time them.
echo "> [ Removing 20 test files to dumpster ]"
for i in {1..20}
	do
		sync
		init=$(date +%s%3N)
		./rm "test$i.txt"
		sync
		final=$(date +%s%3N)
		delta=$((final-init))
		total=$((total + delta))
		echo "Removed test$i.txt in $delta" milliseconds
	done
echo "20 files removed in $total milliseconds"
echo "----------------------------------"

# recover 20 test files and time them.
echo "> [ Recovering 20 test files from dumpster ]"
for i in {1..20}
	do
		sync
		init=$(date +%s%3N)
		./dv "test$i.txt"

		sync
		final=$(date +%s%3N)
		delta=$((final-init))
		total=$((total + delta))
		echo "Recovering test$i.txt in $delta" milliseconds
	done
echo "20 files removed in $total milliseconds"
echo "----------------------------------"

# create 20 versions of test directory and time them.
echo "> [ Making 20 test directories ]"
for i in {1..20}
	do
		sync
		init=$(date +%s%3N)
		#mkdir "test$i"
		cp -r test "test$i"
		sync
		final=$(date +%s%3N)
		delta=$((final-init))
		total=$((total + delta))
	done
echo "20 directories added in $total milliseconds"
echo "----------------------------------"

# remove 20 test directories and time them.
echo "> [ Removing 20 test directories to dumpster ]"
for i in {1..20}
	do
		sync
		init=$(date +%s%3N)
		./rm -r "test$i"
		sync
		final=$(date +%s%3N)
		delta=$((final-init))
		total=$((total + delta))
		echo "Removing test$i in $delta" milliseconds
	done
echo "20 directories removed in $total milliseconds"
echo "----------------------------------"

# recover 20 test directories and time them.
echo "> [ Recovering 20 test directories from dumpster ]"
for i in {1..20}
	do
		sync
		init=$(date +%s%3N)
		./dv "test$i"
		sync
		final=$(date +%s%3N)
		delta=$((final-init))
		total=$((total + delta))
		echo "Recovering test$i in $delta" milliseconds
	done
echo "20 directories recovered in $total milliseconds"
echo "----------------------------------"

# remove 20 test files and directories and time them.
echo "> [ Removing 20 test files and directories to dumpster ]"
for i in {1..20}
	do
		sync
		init=$(date +%s%3N)
		./rm -r "test$i.txt" "test$i"
		sync
		final=$(date +%s%3N)
		delta=$((final-init))
		total=$((total + delta))
		echo "Removing test$i.txt and test$i in $delta" milliseconds
	done
echo "20 files and directories removed in $total milliseconds"
echo "----------------------------------"

# empty the dumpster.
echo "> [ Emptying the Dumpster :) ]"
sync
init=$(date +%s%3N)
./dump
sync
final=$(date +%s%3N)
delta=$((final-init))
total=$((total + delta))
echo "Dumping takes $delta" milliseconds
echo "----------------------------------"
echo "##################################"