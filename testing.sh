#!/bin/bash

# testing.sh
# 
# Jonathan Metzger
#  Spring 2018
#
# Project for CS4513 Distributed Computing Systems
#

export DUMPSTER=dumpster
# partition path other than current directory
partition_path="/media/sf_projects/Dumpster-Diving/dumpster"
partition_path_copy="/media/sf_projects/dumpster_copy"
# get the size of the test file.
filesize_dumpster=$(stat -c%s "$partition_path")
filesize_dumpster_copy=$(stat -c%s "$partition_path_copy")

#################################################

echo
echo "----------------------------------"
echo
echo "Welcome to Dumpster Diving TESTING"
echo "Created by Jonathan Metzger"
echo "{ rm, dv and dump } tool Utility"
echo
echo "----------------------------------"

echo
echo "> [ make clean ]"
echo
make clean

echo
echo "> [ make ]"
echo
make

echo
echo "----------------------------------"
echo

#################################################

# print out the size with dumpster (same or different partition)
echo "[ Partition:	$partition_path ]"
echo "[ Size: 	$filesize_dumpster bytes ]"
echo
echo "----------------------------------"
echo

# create 20 versions of test file.
echo "> [ Making 20 test files ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		echo "hello "> "test$i.txt"

		sync
		# measure the second time.
		t2=$(date +%s%3N)

		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		# echo "Created file test$i.txt in $timeUse" milliseconds
	done

# print out the total time needed and the average time.
echo "20 files added in $totalRenameTime milliseconds"
echo "Average time per file in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo 
# remove these test files and time.
echo "> [ Removing 20 test files to dumpster ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		./rm "test$i.txt"

		sync
		# measure the second time.
		t2=$(date +%s%3N)
		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		echo "Removing test$i.txt in	$timeUse" milliseconds
	done
echo
# print out the total time needed and the average time.
echo "20 files removed in $totalRenameTime milliseconds"
echo "Average time per files in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo

#################################################

# create 20 versions of test directory.
echo "> [ Making 20 test directories ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		# make directory
		mkdir "test$i"

		sync
		# measure the second time.
		t2=$(date +%s%3N)
		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		#echo "Created directory test$i in $timeUse" milliseconds
	done

# print out the total time needed and the average time.
echo "20 directories added in $totalRenameTime milliseconds"
echo "Average time per directory in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo

# remove these test files and time.
echo "> [ Removing 20 test directories to dumpster ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		
		./rm -r "test$i"
		
		sync
		# measure the second time.
		t2=$(date +%s%3N)

		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		echo "Removing test$i in	$timeUse" milliseconds
	done
echo
# print out the total time needed and the average time.
echo "20 directories removed in $totalRenameTime milliseconds"
echo "Average time per directory in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo

#################################################

# empty the dumpster.
echo "> [ Emptying the Dumpster :) ]"

./dump

echo "----------------------------------"
echo

#################################################

# print out the size with dumpster (same or different partition)
echo "[ Partition:	$partition_path_copy ]"
echo "[ Size: 	$filesize_dumpster_copy bytes ]"
echo
echo "----------------------------------"
echo

# create 20 versions of test file.
echo "> [ Making 20 test files ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		echo "hello "> "$partition_path/test$i.txt"

		sync
		# measure the second time.
		t2=$(date +%s%3N)

		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		# echo "Created file test$i.txt in $timeUse" milliseconds
	done

# print out the total time needed and the average time.
echo "20 files added in $totalRenameTime milliseconds"
echo "Average time per file in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo 
# remove these test files and time.
echo "> [ Removing 20 test files to dumpster ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		./rm "$partition_path/test$i.txt"

		sync
		# measure the second time.
		t2=$(date +%s%3N)
		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		echo "Removing test$i.txt in	$timeUse" milliseconds
	done
echo
# print out the total time needed and the average time.
echo "20 files removed in $totalRenameTime milliseconds"
echo "Average time per files in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo

#################################################

# create 20 versions of test directory.
echo "> [ Making 20 test directories ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		# make directory
		mkdir "$partition_path/test$i"

		sync
		# measure the second time.
		t2=$(date +%s%3N)
		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		#echo "Created directory test$i in $timeUse" milliseconds
	done

# print out the total time needed and the average time.
echo "20 directories added in $totalRenameTime milliseconds"
echo "Average time per directory in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo

# remove these test files and time.
echo "> [ Removing 20 test directories to dumpster ]"
for i in {1..20}
	do
		sync
		# measure the first time.
		t1=$(date +%s%3N)
		
		./rm -r "$partition_path/test$i"
		
		sync
		# measure the second time.
		t2=$(date +%s%3N)

		# calculate the time used.
		timeUse=$((t2-t1))
		# add to total time.
		totalRenameTime=$((totalRenameTime + timeUse))
		# print out the time used for one run.
		echo "Removing test$i in	$timeUse" milliseconds
	done
echo
# print out the total time needed and the average time.
echo "20 directories removed in $totalRenameTime milliseconds"
echo "Average time per directory in $((totalRenameTime/20)) milliseconds"
echo
echo "----------------------------------"
echo

#################################################

# empty the dumpster.
echo "> [ Emptying the Dumpster :) ]"

./dump

echo "----------------------------------"
echo

#################################################
