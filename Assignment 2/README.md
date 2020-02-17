# REST API with JSON
This Program will implement a REST API with JSON in Python. It is a server which responds to the requests through REST API and implements GET, PUT, POST, DELETE methods.

# Postman
It has been used to perform integration testing with the REST API. All methods implemented e.g GET, PUT, POST, DELETE ,are checked using it. It simulates how a user interacts with the system.

### Module files
For this application i.e 'REST API with JSON', the Flask,SQL and JSON modules of Python are imported. The main libraries and files are as follows:
| from flask import Flask, request, jsonify | It returns a flask.
| from flask_restful import Resource, Api, reqparse | It an extension of Flask which supports the building of REST APIs for adding , parsing of multiple arguments.
| from sqlalchemy import create_engine | This is database toolkit in python.
| from json import dumps | It takes a json object and returns a string.
| import json | JSON module converts python dictionary into a JSON string so that it can be written to a file


### Attributes

| **Field** | **Description** |
| --------- | --------------- |
| db_connect | it  specifies the database type and name .
| app | It is for initializing the flask applications.
| api  | It is an initializier for the API.
| parser  | It is used for creating a parser which parses the JSON objects.


### Methods used and Description
A database 'Student' has been created on AWS sqlite which contains the details regarding the students : Student ID, Name ,Major with Student ID as the primary key. Two Classes, Student and Students, have been created to manage the Students database.  Following methods have been implemented to access the resources.


### get() - The GET method will request data/details of a specific resource (using primary key ‘student_id)) or all the resources in our database 'Student'. The get(self) method returns the details of al the resources. The get(self, student_id) method returns the details of a specific resource identified by the primary key student_id.

### put() - The PUT() method updates the Student resources of a particular student using the primary key ‘student_id’ in the database.

### post() - The POST method is used to create a new resource in the Student database. It allows a new record to be added in the Student.

### delete() - The DELETE method will remove an existing resource from the database using the primary key ‘student_id’ specified by the user.
