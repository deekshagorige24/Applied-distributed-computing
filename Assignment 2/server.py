#***********************************************************#
#Course : TCSS 558                                          #
#Authors : Deeksha                                          #
#                                                           #
#                                              		    #
# This is a server which responds to the requests through   #
# REST API                                                  #
#***********************************************************#

# Importing Flask,SQL and JSON libraries #
from flask import Flask, request, jsonify
from flask_restful import Resource, Api, reqparse
from sqlalchemy import create_engine
from json import dumps
import json

# Specifying the Database type and name #
db_connect = create_engine('sqlite:///ad.db')
# Initializing the Flask application #
app = Flask(__name__)
# Initializing the API #
api = Api(app)
# Creating a parser to parse the JSON objects #
parser = reqparse.RequestParser()
# Class to route the GET method to get the details of all the resources i e., Student in this case #
class Students(Resource):
    # GET method #
    def get(self):
        conn = db_connect.connect()
        query = conn.execute("select * from STUDENT")
        result = {'data': [dict(zip(tuple (query.keys()) ,i)) for i in query.cursor]}
        return jsonify(result)
# Class to route the GET method to get the details of the specified resource through the unique student_id requested #
class Student(Resource):
    # GET Method with student_id #
    def get(self,student_id):
        conn = db_connect.connect()
	query = conn.execute("select * from STUDENT where id = \"{0}\"".format(student_id))
	result = {'data': [dict(zip(tuple (query.keys()) ,i)) for i in query.cursor]}
        return jsonify(result)

    # PUT Method to Update a resource in the database identified with the unique student_id #
    def put(self,student_id):
        parser.add_argument('name',type=str)
        parser.add_argument('major',type=str)
        args = parser.parse_args(request)    
	lists = []
	s = ""
	final = ""
	k = ""
        for key,value in args.items():
		if key!='id'and value!=None:
			k = k + key
			k = k + "="
			k = k + "'"
			k = k + value
			k = k + "'"
			lists.append(k)
	print(lists)
        for i in range(len(lists)):
		final = final + lists[i]
		final = final + ","
	l = final[:-1]
	print("final is: "+l)
       	conn = db_connect.connect()
        q = ("update STUDENT set "+l+" where id= "+str(student_id))
        query = conn.execute(q)
        return{'Status':'Successfully Edited the record'}
    # POST Method to Create a resourse in the database #
    def post(self):
        conn = db_connect.connect()
        parser.add_argument('name',type=str)
        parser.add_argument('major',type=str)
        parser.add_argument('id',type=str)
        args = parser.parse_args(request)
        print(args)
        query = conn.execute("insert into STUDENT values('{0}','{1}','{2}')".format(args['name'],args['major'],args['id']))
	return{'status':'successfully entered the entry'}

    # Delete Method to Delete an existing resource from the database identified by the unique student_id #
    def delete(self,student_id):
        conn = db_connect.connect()
        query = conn.execute("delete from STUDENT where id="+str(student_id));
	return{'status':'successfully deleted the entry'}

# Routing the /students path to GTE Method in the Students class #
api.add_resource(Students, '/students')
# Routing the /students/student_id path to the mothods of Student class #
api.add_resource(Student, '/students', '/students/<string:student_id>')


# Specifying the host and port numbers on which the server will listen # 
if __name__ == '__main__':
	app.run(debug=True,port = 5000, host = '0.0.0.0')



