Dependencies :: Python2

List of members of 10-tuple metadata generated for each file ::
st_mode: protection bits.
st_ino: inode number.
st_dev: device.
st_nlink: number of hard links.
st_uid: user id of owner.
st_gid: group id of owner.
st_size: size of file, in bytes.
st_atime: time of most recent access.
st_mtime: time of most recent content modification.
st_ctime: time of most recent metadata change.

Commands ::
1. 'create file_name'
This command will create a file 'file_name' in Textfs and add its metadata in 'ramesh.txt'.

2. 'copy file_name external_file_name'
This command will copy contents of external file 'external_file_name' to 'ramesh.txt' and update no. of lines file contents in 'ramesh.txt'.

3. 'delete file_name'
This command will delete file 'file_name' from Textfs and it's contents from 'ramesh.txt'

4. 'echo file_name'
This command will print the contents of file 'file_name' by accessing it in 'ramesh.txt'

5. 'ls'
This command will list all the files of Textfs
