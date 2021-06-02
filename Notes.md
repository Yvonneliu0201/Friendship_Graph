# notes for project
* Profile Data
- name, age, occupation, and a list of friends
- support insert, get user info from index, print all
- insert: insert into a text file
- getUser(index) -> go to specific line in profile txt file and return line in the form of struct user?
- printAll -> prints user,age,occupation,list separated by commas, each user is on diff lines
- name and occupation could have spaces
* Red-Black Tree
- uses name from Profile Data struct User as node
- support insert, exact match search(name), range serach queries
- insert: normal insert, with aut osort to change color and balance out, alphabetical
- range search query: (name) 
- - ie. find the occupations of all users between fuheng and sean
- - ie. find the names of all uesrs between name1 and name2
- - ie. find the ages of all uesrs between name1 and name2

* Friendship Graph