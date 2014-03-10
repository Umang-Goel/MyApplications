# -*- coding: utf-8 -*-
# this file is released under public domain and you can use without limitations

#########################################################################
## This is a samples controller
## - index is the default action of any application
## - user is required for authentication and authorization
## - download is for downloading files uploaded in the db (does streaming)
## - call exposes all registered services (none by default)
#########################################################################

def verification():
        uid=int(request.vars.uid)
        tries=int(request.vars.tries)
        if(tries>2):
            db(db.student.student_id==uid).delete()
            db(db.auth_membership.user_id==auth.user_id).delete()
            db(db.auth_user.id==uid).delete()
            redirect(URL('delete_page'))
            response.flash = T("Sorry, Your account has been deleted")
            return dict();
        else:
            receiver=(str(db((db.auth_user.id==uid)).select(db.auth_user.email))).split('\r\n')
            mail.send(receiver[1], subject='Test Message Resume-Builder', message='This is a test message.\nYour Code Number is '+str(uid))
            form = SQLFORM.factory( 
                    db.Field('email_id','string',requires=IS_EMAIL(),required=True),
                    db.Field('idno','integer',required=True,label="Verification Code"))
            if form.accepts(request.vars,session):
		if(uid==int(form.vars.idno)):
                    response.flash = T("Thank you for registering")
                    redirect(URL('edit_personal_detail'))	
                if(uid!=int(form.vars.idno)):
                    response.flash = T("Sorry not matching")
                    tries=tries+1
                    redirect(URL('verification',vars=dict(uid=uid,tries=tries)))
            elif form.errors:
                    response.flash='Errors in form'
            return dict(form=form)
       
def verification_comp():
        uid=int(request.vars.uid)
        tries=int(request.vars.tries)
        if(tries>2):
            db(db.student.student_id==uid).delete()
            db(db.auth_membership.user_id==auth.user_id).delete()
            db(db.auth_user.id==uid).delete()
            redirect(URL('delete_page'))
            response.flash = T("Sorry, Your account has been deleted")
            return dict();
        else:
            receiver=(str(db((db.auth_user.id==uid)).select(db.auth_user.email))).split('\r\n')
            mail.send(receiver[1], subject='Test Message Resume-Builder', message='This is a test message.\nYour Code Number is '+str(uid))
            form = SQLFORM.factory( 
                    db.Field('email_id','string',requires=IS_EMAIL(),required=True),
                    db.Field('idno','integer',required=True))
            if form.accepts(request.vars,session):
		if(uid==int(form.vars.idno)):
                    response.flash = T("Thank you for registering")
                    redirect(URL('edit_company_details'))	
                if(uid!=int(form.vars.idno)):
                    response.flash = T("Sorry not matching")
                    tries=tries+1
                    redirect(URL('verification_comp',vars=dict(uid=uid,tries=tries)))
            elif form.errors:
                    response.flash='Errors in form'
            return dict(form=form)
       
def delete_page():
        response.flash = T("Sorry, Your account has been deleted")
	return locals()

def search_institution1():
    links=[lambda row: A('View Resume',_href=URL('temp_func',args=[row.student_id]))]
    grid = SQLFORM.grid(db.institution,fields=[db.institution.student_name,db.institution.student_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def search_workexp():
    links=[lambda row: A('View Resume',_href=URL('temp_func',args=[row.student_id]))]
    grid = SQLFORM.grid(db.work_expr,fields=[db.work_expr.student_name,db.work_expr.student_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def search_project():
    links=[lambda row: A('View Resume',_href=URL('temp_func',args=[row.student_id]))]
    grid = SQLFORM.grid(db.project,fields=[db.project.student_name,db.project.student_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def search_course():
    links=[lambda row: A('View Resume',_href=URL('temp_func',args=[row.student_id]))]
    grid = SQLFORM.grid(db.course,fields=[db.course.student_name,db.course.student_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def search_name():
    links=[lambda row: A('View Resume',_href=URL('temp_func',args=[row.student_id]))]
    grid = SQLFORM.grid(db.student,fields=[db.student.name,db.student.student_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def search_mincgpa1():
    form=SQLFORM.factory(
            db.Field('Min_Cgpa','double',required=True,label='Enter Min Gcpa'))
    if form.accepts(request.vars, session):
        redirect(URL(r=request, f='search_mincgpa2?Min_Cgpa=%d' % form.vars.Min_Cgpa))
    elif form.errors:
        response.flash = 'Error'
    return dict(form=form)
    
def search_mincgpa2():
        links=[lambda row: A('View Resume',_href=URL('temp_func',args=[row.student_id]))]
        Min_Cgpa=request.vars.Min_Cgpa
        grid = SQLFORM.grid(db.student.cgpa >= Min_Cgpa,fields=[db.student.name,db.student.student_id],deletable=False, editable=False,details=False,links=links)
        return dict(grid=grid)


def search_comp_name():
    links=[lambda row: A('View Resume',_href=URL('search_page_company',args=[row.company_id]))]
    grid = SQLFORM.grid(db.company,fields=[db.company.name,db.company.company_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def search_job_post():
    links=[lambda row: A('View Resume',_href=URL('search_page_company',args=[row.company_id]))]
    grid = SQLFORM.grid(db.vacancy,fields=[db.vacancy.company_name,db.vacancy.company_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def search_job_req():
    links=[lambda row: A('View Resume',_href=URL('search_page_company',args=[row.company_id]))]
    grid = SQLFORM.grid(db.req_com,fields=[db.req_com.company_name,db.req_com.company_id],deletable=False, editable=False,details=False,links=links)
    return dict(grid=grid)

def advanced_search():
    form=SQLFORM.factory(
            db.Field('search','string',requires=IS_IN_SET(['Min cgpa criteria','Name','Institution','Work Experience','Project','Course','Company Name','Job Post','Job Requirement']),label='Search Option:'))
    if form.accepts(request.vars, session):
        redirect(URL(r=request, f='advanced_search_option?search=%s' % form.vars.search))
    elif form.errors:
        response.flash = 'Error'
    return dict(form=form)
    
def advanced_search_option():
    search=request.vars.search
    if(search=="Min cgpa criteria"):
        redirect(URL(r=request, f='search_mincgpa1'))
    elif(search=="Name"):
        redirect(URL(r=request, f='search_name'))
    elif(search=="Institution"):
        redirect(URL(r=request, f='search_institution1'))
    elif(search=="Work Experience"):
        redirect(URL(r=request, f='search_workexp'))
    elif(search=="Project"):
        redirect(URL(r=request, f='search_project'))
    elif(search=="Course"):
        redirect(URL(r=request, f='search_course'))
    elif(search=="Company Name"):
        redirect(URL(r=request, f='search_comp_name'))
    elif(search=="Job Post"):
        redirect(URL(r=request, f='search_job_post'))
    elif(search=="Job Requirement"):
        redirect(URL(r=request, f='search_job_req'))
        
@auth.requires_login()
def index():
    """
    example action using the internatiornalization operator T and flash
    rendered by views/default/index.html or views/generic.html

    if you need a simple wiki simple replace the two lines below with:
    return auth.wiki()
    """
    ar=db((db.auth_membership.user_id==auth.user_id) & (db.auth_group.id==db.auth_membership.group_id)).select(db.auth_group.role)
    if(len(ar)==0):
        redirect(URL(r=request, f='user'))
    elif(len(ar)==1):
        redirect(URL(r=request, f='new_register'))
    elif(ar[1]['role']=='student'):
        redirect(URL(r=request, f='select_view'))
    elif(ar[1]['role']=='company'):
        redirect(URL(r=request, f='page_company'))
    
def new_register():
    form=SQLFORM.factory(
            db.Field('group','string',requires=IS_IN_SET(['student','company'])))
    if form.accepts(request.vars,session):
        redirect(URL(r=request, f='insert_group?group=%s' % form.vars.group))
    elif form.errors:
        response.flash='Errors in form'
    return dict(form=form)

def insert_group():
    query=request.vars.group
    if(query=="student"):
        var=db(db.auth_group.role=='student').select(db.auth_group.id)
        db.auth_membership.insert(user_id=auth.user_id,group_id=var[0]['id'])
        redirect(URL('verification',vars=dict(uid=auth.user_id,tries=0)))
    elif(query=="company"):
        var=db(db.auth_group.role=='company').select(db.auth_group.id)
        db.auth_membership.insert(user_id=auth.user_id,group_id=var[0]['id'])
        redirect(URL('verification_comp',vars=dict(uid=auth.user_id,tries=0)))

@auth.requires_login()
def edit_personal_detail():
    response.flash = T("Welcome Student")
    ar1=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name,db.auth_user.email)
    db.student.name.default=ar1[0].first_name+" "+ar1[0].last_name
    db.student.name.writable=False
    db.student.name.readable=False
    db.student.email.default=ar1[0].email
    db.student.email.readable=False
    db.student.email.writable=False
    db.student.student_id.default=auth.user_id
    db.student.student_id.readable=False
    db.student.student_id.writable=False
    db.student.def_temp.default="1"
    db.student.def_temp.readable=False
    db.student.def_temp.writable=False
    form=SQLFORM(db.student)
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)           
    ##return locals()

def select_view():
	query=db(db.student.student_id==auth.user_id).select(db.student.def_temp)
#	if(len(query)==0):
 #           redirect(URL(r=request, f='edit_personal_detail'))
	if(query[0].def_temp=="1"):
            redirect(URL(r=request, f='page_student'))
	if(query[0].def_temp=="2"):
            redirect(URL(r=request, f='page_student2'))
     	else:
            redirect(URL(r=request, f='page_student3'))

#@auth.requires_login()
##ef company_login():
 #   response.flash = T("Welcome Company")    
  #  return locals()

#def temp_student():
 #   ar=db(db.student.id>0).select(db.student.id)
  #  db.student_table.insert(table_id=ar[-1]['id'],student_id=auth.user_id)
   # redirect(URL(r=request, f='page_student'))
    
@auth.requires_login()
def page_student():
    name=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    personal=db(db.student.student_id==auth.user_id).select(db.student.ALL)
    courses=db(db.course.student_id==auth.user_id).select(db.course.ALL)
    projects=db(db.project.student_id==auth.user_id).select(db.project.ALL)
    activities=db(db.activity.student_id==auth.user_id).select(db.activity.ALL)
    extras=db(db.extra.student_id==auth.user_id).select(db.extra.ALL)
    work=db(db.work_expr.student_id==auth.user_id).select(db.work_expr.ALL)
    #institutions=db((db.institution_table.student_id==auth.user_id) & (db.institution.id==db.institution_table.table_id)).select(db.institution.name)
    institutions=db(db.institution.student_id==auth.user_id).select(db.institution.ALL)
    coments=db((db.coment.receiver==auth.user_id) & (db.auth_user.id==db.coment.sender_id)).select(db.coment.body,db.auth_user.first_name,db.auth_user.last_name,db.coment.likes,db.coment.id)
    
    form=SQLFORM.factory(
	 db.Field('comm_body','string',label=""),
	 formstyle='divs',
	 buttons=[],)
    form[0].insert(1,DIV(INPUT(_type='submit',_value='Post')))
    if form.accepts(request.vars,session):
         insert_comment(form.vars.comm_body,auth.user_id)
    elif form.errors:
         response.flash='Some Error Occured Please Refresh'
    
    return dict(personal=personal,courses=courses,projects=projects,activities=activities,extras=extras,institutions=institutions,coments=coments,form=form,work=work,name=name)
    
@auth.requires_login()
def page_student2():
    name=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    personal=db(db.student.student_id==auth.user_id).select(db.student.ALL)
    courses=db(db.course.student_id==auth.user_id).select(db.course.ALL)
    projects=db(db.project.student_id==auth.user_id).select(db.project.ALL)
    activities=db(db.activity.student_id==auth.user_id).select(db.activity.ALL)
    extras=db(db.extra.student_id==auth.user_id).select(db.extra.ALL)
    work=db(db.work_expr.student_id==auth.user_id).select(db.work_expr.ALL)
    #institutions=db((db.institution_table.student_id==auth.user_id) & (db.institution.id==db.institution_table.table_id)).select(db.institution.name)
    institutions=db(db.institution.student_id==auth.user_id).select(db.institution.ALL)
    coments=db((db.coment.receiver==auth.user_id) & (db.auth_user.id==db.coment.sender_id)).select(db.coment.body,db.auth_user.first_name,db.auth_user.last_name,db.coment.likes,db.coment.id)
    
    form=SQLFORM.factory(
	 db.Field('comm_body','string',label=""),
	 formstyle='divs',
	 buttons=[],)
    form[0].insert(1,DIV(INPUT(_type='submit',_value='Post')))
    if form.accepts(request.vars,session):
         insert_comment(form.vars.comm_body,auth.user_id)
    elif form.errors:
         response.flash='Some Error Occured Please Refresh'
    
    return dict(personal=personal,courses=courses,projects=projects,activities=activities,extras=extras,institutions=institutions,coments=coments,form=form,work=work,name=name)
   

@auth.requires_login()
def page_student3():
    name=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    personal=db(db.student.student_id==auth.user_id).select(db.student.ALL)
    courses=db(db.course.student_id==auth.user_id).select(db.course.ALL)
    projects=db(db.project.student_id==auth.user_id).select(db.project.ALL)
    activities=db(db.activity.student_id==auth.user_id).select(db.activity.ALL)
    extras=db(db.extra.student_id==auth.user_id).select(db.extra.ALL)
    work=db(db.work_expr.student_id==auth.user_id).select(db.work_expr.ALL)
    #institutions=db((db.institution_table.student_id==auth.user_id) & (db.institution.id==db.institution_table.table_id)).select(db.institution.name)
    institutions=db(db.institution.student_id==auth.user_id).select(db.institution.name,db.institution.title)
    coments=db((db.coment.receiver==auth.user_id) & (db.auth_user.id==db.coment.sender_id)).select(db.coment.body,db.auth_user.first_name,db.auth_user.last_name,db.coment.likes,db.coment.id)
    
    form=SQLFORM.factory(
	 db.Field('comm_body','string',label=""),
	 formstyle='divs',
	 buttons=[],)
    form[0].insert(1,DIV(INPUT(_type='submit',_value='Post')))
    if form.accepts(request.vars,session):
         insert_comment(form.vars.comm_body,auth.user_id)
    elif form.errors:
         response.flash='Some Error Occured Please Refresh'
    
    return dict(personal=personal,courses=courses,projects=projects,activities=activities,extras=extras,institutions=institutions,coments=coments,form=form,work=work,name=name)
    

@auth.requires_login()
def edit_course():
    response.flash = T("Enter course")
    ar1=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    db.course.student_name.default=ar1[0].first_name+" "+ar1[0].last_name
    db.course.student_name.writable=False
    db.course.student_name.readable=False
    db.course.student_id.default=auth.user_id
    db.course.student_id.readable=False
    db.course.student_id.writable=False
    form=SQLFORM(db.course,submit_button="Enter Course",labels={'name':'Name of Course'},formstyle="divs")
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)
 
#def temp_course():
 #   ar=db(db.course.id>0).select(db.course.id)
  #  db.course_table.insert(table_id=ar[-1]['id'],student_id=auth.user_id)
   # redirect(URL(r=request, f='page_student')) 

@auth.requires_login()
def edit_project():
    response.flash = T("Enter project")
    ar1=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    db.project.student_name.default=ar1[0].first_name+" "+ar1[0].last_name
    db.project.student_name.writable=False
    db.project.student_name.readable=False
    db.project.student_id.default=auth.user_id
    db.project.student_id.readable=False
    db.project.student_id.writable=False
    form=SQLFORM(db.project,submit_button="Enter",labels={'name':'Name of Project','detail':'Details'},formstyle="divs")
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)
    
#def temp_project():
 #   ar=db(db.project.id>0).select(db.project.id)
  #  db.project_table.insert(table_id=ar[-1]['id'],student_id=auth.user_id)
   # redirect(URL(r=request, f='page_student'))
    #return dict(ar=ar)
    
@auth.requires_login()
def edit_activity():
    ar1=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    db.activity.student_name.default=ar1[0].first_name+" "+ar1[0].last_name
    db.activity.student_name.writable=False
    db.activity.student_name.readable=False
    db.activity.student_id.default=auth.user_id
    db.activity.student_id.readable=False
    db.activity.student_id.writable=False
    response.flash = T("Enter Achievement")
    form=SQLFORM(db.activity,submit_button="Enter",labels={'title':'Name of Achievement','detail':'Details'},formstyle="divs")
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)
    
#def temp_activity():
 #   ar=db(db.activity.id>0).select(db.activity.id)
  #  db.activity_table.insert(table_id=ar[-1]['id'],student_id=auth.user_id)
   # redirect(URL(r=request, f='page_student'))
    #return dict(ar=ar)

    
@auth.requires_login()
def edit_extra():
    response.flash = T("Enter Other Details")
    ar1=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    db.extra.student_name.default=ar1[0].first_name+" "+ar1[0].last_name
    db.extra.student_name.writable=False
    db.extra.student_name.readable=False
    db.extra.student_id.default=auth.user_id
    db.extra.student_id.readable=False
    db.extra.student_id.writable=False
    form=SQLFORM(db.extra,submit_button="Enter",labels={'title':'Kind/Name of Activity','detail':'Details'},formstyle="divs")
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)
    
@auth.requires_login()
def edit_work_expr():
    response.flash = T("Enter Work Experience")
    ar1=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    db.work_expr.student_name.default=ar1[0].first_name+" "+ar1[0].last_name
    db.work_expr.student_name.writable=False
    db.work_expr.student_name.readable=False
    db.work_expr.student_id.default=auth.user_id
    db.work_expr.student_id.readable=False
    db.work_expr.student_id.writable=False
    form=SQLFORM(db.work_expr,submit_button="Enter",labels={'name':'Name of Company','as_post':'Your Post','type_of':'Intern or Job','start_time':'Joined At','end_time':'Left At','is_left':'Still Continuing'})
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)

#def temp_extra():
 #   ar=db(db.extra.id>0).select(db.extra.id)
  #  db.extra_table.insert(table_id=ar[-1]['id'],student_id=auth.user_id)
   # redirect(URL(r=request, f='page_student'))
    #return dict(ar=ar)
 
@auth.requires_login()
def delete_course():
      form=SQLFORM.factory(
            db.Field('query','string',requires=IS_IN_DB(db(db.course.student_id==auth.user_id),'course.name','course.name',distinct=True),label='Enter Course'))
      if form.accepts(request.vars, session):
          redirect(URL(r=request, f='temp_del_course?query=%s' % form.vars.query))
      elif form.errors:
         response.flash = 'Error'
      return dict(form=form)
     
@auth.requires_login()
def temp_del_course():
      query=request.vars.query
#      ar_id=db(db.course.name==query).select(db.course.id)
      db(((db.course.name).lower()==query.lower()) & (db.course.student_id==auth.user_id)).delete()
    #  for x in ar_id:
     #     ar_table=db((db.course_table.student_id==auth.user_id) & (db.course_table.table_id==x['id'])).select(db.course_table.id)
      #    if(len(ar_table)):
       #       db(db.course_table.id==ar_table[0]['id']).delete()
	#      break
      redirect(URL(r=request, f='select_view'))
    
@auth.requires_login()
def delete_project():
      form=SQLFORM.factory(
            db.Field('query','string',requires=IS_IN_DB(db((auth.user_id==db.project.student_id)),'project.name','project.name',distinct=True),label='Enter Project'))
      if form.accepts(request.vars, session):
          redirect(URL(r=request, f='temp_del_project?query=%s' % form.vars.query))
      elif form.errors:
         response.flash = 'Error'
      return dict(form=form)
     
@auth.requires_login()
def temp_del_project():
      query=request.vars.query
      db(((db.project.name).lower()==query.lower()) & (db.project.student_id==auth.user_id)).delete()
      redirect(URL(r=request, f='select_view'))
      #return dict(ar_table==ar_table)
     
@auth.requires_login()
def delete_work_expr():
      form=SQLFORM.factory(
            db.Field('query1','string',requires=IS_IN_DB(db(auth.user_id==db.work_expr.student_id),'work_expr.name','work_expr.name',distinct=True),label='Enter name of Company'),
            db.Field('query2','string',requires=IS_IN_SET(['intern','employ']),required=True,label='Enter type'))
      if form.accepts(request.vars, session):
          redirect(URL(r=request, f='temp_del_work_expr',args=[form.vars.query1,form.vars.query2]))
      elif form.errors:
         response.flash = 'Error'
      return dict(form=form)
     
@auth.requires_login()
def temp_del_work_expr():
      q1=request.args(0)
      q2=request.args(1)
      db(((db.work_expr.name).lower()==q1.lower()) & (db.work_expr.type_of==q2) & (db.work_expr.student_id==auth.user_id)).delete()
      redirect(URL(r=request, f='select_view'))

@auth.requires_login()
def delete_extra():
      form=SQLFORM.factory(
            db.Field('query','string',requires=IS_IN_DB(db(db.extra.student_id==auth.user_id),'extra.title','extra.title',distinct=True),label='Enter Title'))
      if form.accepts(request.vars, session):
          redirect(URL(r=request, f='temp_del_extra?query=%s' % form.vars.query))
      elif form.errors:
         response.flash = 'Error'
      return dict(form=form)
     
@auth.requires_login()
def temp_del_extra():
      query=request.vars.query

      db((db.extra.title==query) & (db.extra.student_id==auth.user_id)).delete()
      redirect(URL(r=request, f='select_view'))
      
@auth.requires_login()
def delete_activity():
      form=SQLFORM.factory(
            db.Field('query','string',requires=IS_IN_DB(db(db.activity.student_id==auth.user_id),'activity.title','activity.title',distinct=True),label='Enter Title'))
      if form.accepts(request.vars, session):
          redirect(URL(r=request, f='temp_del_activity?query=%s' % form.vars.query))
      elif form.errors:
         response.flash = 'Error'
      return dict(form=form)
     
@auth.requires_login()
def temp_del_activity():
      query=request.vars.query
      ar_table=db((db.activity.title.lower()==query.lower()) & (db.activity.student_id==auth.user_id)).delete()
      redirect(URL(r=request, f='select_view'))
    
def temp_company():
    ar=db(db.company.id>0).select(db.company.id)
    db.student_table.insert(table_id=ar[-1]['id'],company_id=auth.user_id)
    redirect(URL(r=request, f='page_company'))

@auth.requires_login()
def send_message():
    response.flash = T("Enter Message")
    db.messages.student_id.default=auth.user_id
    db.messages.student_id.readable=False
    db.messages.student_id.writable=False
    form=SQLFORM(db.messages)
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)

#def temp_message():
 #   ar=db(db.messages.id>0).select(db.messages.id)
  #  db.message_table.insert(table_id=ar[-1]['id'],student_id=auth.user_id)
   # redirect(URL(r=request, f='page_student'))

@auth.requires_login()
def view_message():
	ar=db((db.messages.receiver_id==auth.user_id) & (db.auth_user.id==db.messages.student_id)).select(db.auth_user.first_name,db.messages.body)
	return dict(ar=ar)

@auth.requires_login()
def edit_institution():
    ar1=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name,db.auth_user.last_name)
    db.institution.student_name.default=ar1[0].first_name+" "+ar1[0].last_name
    db.institution.student_name.writable=False
    db.institution.student_name.readable=False
    db.institution.student_id.default=auth.user_id
    db.institution.student_id.readable=False
    db.institution.student_id.writable=False
    response.flash = T("Enter Institution")
    form=SQLFORM(db.institution,submit_button="Enter",labels={'title':'Type of institution','grade':'Grades'})
    if form.process().accepted:
            redirect(URL(r=request, f='select_view'))
    elif form.errors:
            response.flash='Errors in form'
    return dict(form=form)
    
#def temp_institution():
#    ar=db(db.institution.id>0).select(db.institution.id)
 #   db.institution_table.insert(table_id=ar[-1]['id'],student_id=auth.user_id)
  #  redirect(URL(r=request, f='page_student'))
    #return dict(ar=ar)

@auth.requires_login()
def delete_institution():
      form=SQLFORM.factory(
            db.Field('query','string',label='Enter Institution Type'))
      if form.accepts(request.vars, session):
          redirect(URL(r=request, f='temp_del_institution?query=%s' % form.vars.query))
      elif form.errors:
         response.flash = 'Error'
      return dict(form=form)
     
@auth.requires_login()
def temp_del_institution():
      query=request.vars.query
    #  ar_id=db(db.institution.name==query).select(db.institution.id)
     # for x in ar_id:
      db((db.institution.student_id==auth.user_id) & (db.institution.title.lower()==query.lower())).delete()
      #    if(len(ar_table)):
       #       db(db.institution_table.id==ar_table[0]['id']).delete()
	#      break
      redirect(URL(r=request, f='select_view'))
   
@auth.requires_login()
def insert_comment(c_body,rec):
        db.coment.insert(body=c_body,sender_id=auth.user_id,likes=0,receiver=int(rec))
        query=db(db.coment.id>0).select(db.coment.id,db.coment.receiver)
        if(int(query[-1].receiver)==int(auth.user_id)):
            redirect(URL(r=request, f='select_view'))
        else:
            redirect(URL(r=request, f='temp_func',args=[int(query[-1].receiver)]))
        
@auth.requires_login()
def delete_comment():
       form=SQLFORM.factory(
             db.Field('req','integer',label='Select Comment No.'))
       if form.accepts(request.vars, session):
           redirect(URL(r=request, f='temp_del_coment?req=%s' % form.vars.req))
       elif form.errors:
         response.flash = 'Error'
       return dict(form=form)

@auth.requires_login()
def temp_del_coment():
	query=(int)(request.vars.req)
	ar=db(db.coment.id>0).select(db.coment.receiver,db.coment.id)
	y=0
	for x in ar:
		if(int(x.receiver)==int(auth.user_id)):
			y=y+1
		if(y==query):
			db(db.coment.id==x.id).delete()
#			db(db.coment_table.id==x.id).delete()
			break
#	dont remove this comment   return dict(query=query,ar=ar,user=auth.user_id,y=y)
        redirect(URL(r=request, f='select_view'))
		
def temp_func():
	rec=int(request.args(0))
	query=db(db.student.student_id==rec).select(db.student.def_temp)
	if(query[0].def_temp=="1"):
            redirect(URL(r=request, f='view_page1',args=[int(rec)]))
	elif(query[0].def_temp=="2"):
            redirect(URL(r=request, f='view_page2',args=[int(rec)]))
	elif(query[0].def_temp=="3"):
            redirect(URL(r=request, f='view_page3',args=[int(rec)]))
	
def view_page1():
    user_profile=(int)(request.args(0))
    name=db(db.auth_user.id==user_profile).select(db.auth_user.first_name,db.auth_user.last_name)
    personal=db((db.student.student_id==user_profile)).select(db.student.ALL)
    courses=db((db.course.student_id==user_profile)).select(db.course.ALL)
    projects=db((db.project.student_id==user_profile)).select(db.project.ALL)
    activities=db((db.activity.student_id==user_profile)).select(db.activity.ALL)
    extras=db((db.extra.student_id==user_profile)).select(db.extra.ALL)
    institutions=db((db.institution.student_id==user_profile)).select(db.institution.ALL)
    work=db(db.work_expr.student_id==user_profile).select(db.work_expr.ALL)
#    coments=db(db.coment.receiver==user_profile).select(db.coment.body,db.coment.sender,db.coment.likes)
    coments=db((db.coment.receiver==user_profile) & (db.auth_user.id==db.coment.sender_id)).select(db.coment.body,db.auth_user.first_name,db.auth_user.last_name,db.coment.likes,db.coment.id,db.coment.receiver)
    
    form=SQLFORM.factory(
	 Field('comm_body','string',label=""),
	 formstyle='divs',
	 buttons=[],)
    form[0].insert(1,DIV(INPUT(_type='submit',_value='Post')))
    if form.accepts(request.vars,session):
         insert_comment(form.vars.comm_body,user_profile)
    elif form.errors:
         response.flash='Some Error Occured Please Refresh'
    
    return dict(personal=personal,courses=courses,projects=projects,activities=activities,extras=extras,institutions=institutions,coments=coments,form=form,work=work,name=name)


def view_page2():
    user_profile=(int)(request.args(0))
    name=db(db.auth_user.id==user_profile).select(db.auth_user.first_name,db.auth_user.last_name)
    personal=db((db.student.student_id==user_profile)).select(db.student.ALL)
    courses=db((db.course.student_id==user_profile)).select(db.course.ALL)
    projects=db((db.project.student_id==user_profile)).select(db.project.ALL)
    activities=db((db.activity.student_id==user_profile)).select(db.activity.ALL)
    extras=db((db.extra.student_id==user_profile)).select(db.extra.ALL)
    institutions=db((db.institution.student_id==user_profile)).select(db.institution.ALL)
    work=db(db.work_expr.student_id==user_profile).select(db.work_expr.ALL)
#    coments=db(db.coment.receiver==user_profile).select(db.coment.body,db.coment.sender,db.coment.likes)
    coments=db((db.coment.receiver==user_profile) & (db.auth_user.id==db.coment.sender_id)).select(db.coment.body,db.auth_user.first_name,db.auth_user.last_name,db.coment.likes,db.coment.id)
    
    form=SQLFORM.factory(
	 db.Field('comm_body','string',label=""),
	 formstyle='divs',
	 buttons=[],)
    form[0].insert(1,DIV(INPUT(_type='submit',_value='Post')))
    if form.accepts(request.vars,session):
         insert_comment(form.vars.comm_body,user_profile)
    elif form.errors:
         response.flash='Some Error Occured Please Refresh'
    
    return dict(personal=personal,courses=courses,projects=projects,activities=activities,extras=extras,institutions=institutions,coments=coments,form=form,work=work,name=name)


def view_page3():
    user_profile=(int)(request.args(0))
    name=db(db.auth_user.id==user_profile).select(db.auth_user.first_name,db.auth_user.last_name)
    personal=db((db.student.student_id==user_profile)).select(db.student.ALL)
    courses=db((db.course.student_id==user_profile)).select(db.course.ALL)
    projects=db((db.project.student_id==user_profile)).select(db.project.ALL)
    activities=db((db.activity.student_id==user_profile)).select(db.activity.ALL)
    extras=db((db.extra.student_id==user_profile)).select(db.extra.ALL)
    institutions=db((db.institution.student_id==user_profile)).select(db.institution.ALL)
    work=db(db.work_expr.student_id==user_profile).select(db.work_expr.ALL)
#    coments=db(db.coment.receiver==user_profile).select(db.coment.body,db.coment.sender,db.coment.likes)
    coments=db((db.coment.receiver==user_profile) & (db.auth_user.id==db.coment.sender_id)).select(db.coment.body,db.auth_user.first_name,db.auth_user.last_name,db.coment.likes,db.coment.id)
    
    form=SQLFORM.factory(
	 db.Field('comm_body','string',label=""),
	 formstyle='divs',
	 buttons=[],)
    form[0].insert(1,DIV(INPUT(_type='submit',_value='Post')))
    if form.accepts(request.vars,session):
         insert_comment(form.vars.comm_body,user_profile)
    elif form.errors:
         response.flash='Some Error Occured Please Refresh'
    
    return dict(personal=personal,courses=courses,projects=projects,activities=activities,extras=extras,institutions=institutions,coments=coments,form=form,work=work,name=name)


@auth.requires_login()
def like_comment():
	id_rec=int(request.args(0))
#	page_id=int(request.args(1))
	query=db((db.liked_comment.user_id==auth.user_id) & (db.liked_comment.comment_id==id_rec)).select(db.liked_comment.liked)
	q1=db(db.coment.id==id_rec).select(db.coment.likes,db.coment.receiver)
#	redirect(URL(r=request, f='check_view',args=[q1[0].receiver]))
	if(len(query)==0) :
		db.liked_comment.insert(user_id=auth.user_id,comment_id=id_rec)
		db(db.coment.id==id_rec).update(likes=q1[0].likes+1)
	if(int(q1[0].receiver)==int(auth.user_id)):
		redirect(URL(r=request, f='select_view',args=[q1[0].receiver]))
	else :
		redirect(URL(r=request, f='temp_func',args=[q1[0].receiver]))

#def check_view():
#	q1=int(request.args(0))
#	return dict(q1=q1)

@auth.requires_login()
def edit_company_details():
	name=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name)
	db.company.company_id.default=auth.user_id
	db.company.company_id.readable=False
	db.company.company_id.writable=False
	db.company.name.default=name[0].first_name
	db.company.name.readable=False
	db.company.name.writable=False
	form=SQLFORM(db.company,submit_button="Insert It")
	if form.process().accepted:
            redirect(URL(r=request, f='page_company'))
	elif form.errors:
            response.flash='Errors in form'
    	return dict(form=form)           

@auth.requires_login()
def page_company():
	basic=db(db.company.company_id==auth.user_id).select(db.company.ALL)
	vacancies=db(db.vacancy.company_id==auth.user_id).select(db.vacancy.ALL)
	req=[]
	for x in vacancies:
		query=db(db.req_com.vacancy_id==x.id).select(db.req_com.ALL)
		req.append(query)
	return dict(basic=basic,vacancies=vacancies,req=req)
		
def search_page_company():
	query1=int(request.args(0))
	basic=db(db.company.company_id==query1).select(db.company.ALL)
	vacancies=db(db.vacancy.company_id==query1).select(db.vacancy.ALL)
	req=[]
	for x in vacancies:
		query=db(db.req_com.vacancy_id==x.id).select(db.req_com.ALL)
		req.append(query)
	return dict(basic=basic,vacancies=vacancies,req=req)
		
@auth.requires_login()
def edit_vacancy():
	name=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name)
	db.vacancy.company_name.default=name[0].first_name
	db.vacancy.company_name.readable=False
	db.vacancy.company_name.writable=False
	db.vacancy.company_id.default=auth.user_id
	db.vacancy.company_id.readable=False
	db.vacancy.company_id.writable=False
	form=SQLFORM(db.vacancy,submit_button="Enter",label={'post_com':'Post'})
	if form.process().accepted:
            redirect(URL(r=request, f='page_company'))
	elif form.errors:
            response.flash='Errors in form'
    	return dict(form=form)           

@auth.requires_login()
def edit_requirements():
	query=int(request.args(0))
	name=db(db.auth_user.id==auth.user_id).select(db.auth_user.first_name)
	db.req_com.company_name.default=name[0].first_name
	db.req_com.company_name.readable=False
	db.req_com.company_name.writable=False
	db.req_com.company_id.default=auth.user_id
	db.req_com.company_id.readable=False
	db.req_com.company_id.writable=False
	db.req_com.vacancy_id.default=query
	db.req_com.vacancy_id.readable=False
	db.req_com.vacancy_id.writable=False
	form=SQLFORM(db.req_com,submit_button="Enter",labels={'req_name':'Title','req_det':'Detail'})
	if form.process().accepted:
            redirect(URL(r=request, f='page_company'))
	elif form.errors:
            response.flash='Errors in form'
    	return dict(form=form)           

@auth.requires_login()
def del_vacancy():
	form=SQLFORM.factory(
		db.Field('query','string',label='Enter Post'))
      	if form.accepts(request.vars, session):
        	temp_del_vacancy(form.vars.query)
      	elif form.errors:
         	response.flash = 'Error'
    	return dict(form=form)
     
@auth.requires_login()
def temp_del_vacancy(ans):
	q1=db((db.vacancy.post_com.lower()==ans.lower()) & (db.vacancy.company_id==auth.user_id)).select(db.vacancy.id)
	if(len(q1)):
		db(db.req_com.vacancy_id==q1[0].id).delete()
		db((db.vacancy.post_com.lower()==ans.lower()) & (db.vacancy.company_id==auth.user_id)).delete()
        redirect(URL(r=request, f='page_company'))

@auth.requires_login()
def del_requirements():
	ans=int(request.args(0))
	form=SQLFORM.factory(
		db.Field('query','string',label='Enter Title'))
      	if form.accepts(request.vars, session):
        	temp_del_req(form.vars.query,ans)
      	elif form.errors:
         	response.flash = 'Error'
    	return dict(form=form)
     
@auth.requires_login()
def temp_del_req(name,vac_id):
	#name=request.args(0)
	#vac_id=int(request.args(1))
	db((db.req_com.vacancy_id==vac_id) & (db.req_com.req_name.lower()==name.lower())).delete()
        redirect(URL(r=request, f='page_company'))

def search_name1():
        links=[lambda row: A('View Resume',_href=URL('temp_func',args=[row.student_id]))]
        given_name=request.vars.query
        grid = SQLFORM.grid(db.student.name==given_name,fields=[db.student.name,db.student.student_id],deletable=False, editable=False,details=False,links=links)
        return dict(grid=grid)

def view_temp():
	query=(str)(request.vars.which_temp)
	if(query=='1'):
            redirect(URL(r=request, f='page_student'))
	elif(query=='2'):
            redirect(URL(r=request, f='page_student2'))
     	else:
            redirect(URL(r=request, f='page_student3'))

def set_def_temp():
	query=request.vars.def_tmp
        db(db.student.student_id==auth.user_id).update(def_temp = query)
        redirect(URL(r=request, f='select_view'))
	
def update_age():
	form=SQLFORM.factory(
		db.Field('query','integer',label='Enter new age'))
      	if form.accepts(request.vars, session):
        	db(db.student.student_id==auth.user_id).update(age=int(form.vars.query))
        	redirect(URL(r=request, f='select_view'))
    		return dict(form=form)
      	elif form.errors:
         	response.flash = 'Error'
    	return dict(form=form)

def update_contact():
	form=SQLFORM.factory(
		db.Field('query','string',label='Enter new contact'))
      	if form.accepts(request.vars, session):
        	db(db.student.student_id==auth.user_id).update(contact=form.vars.query)
        	redirect(URL(r=request, f='select_view'))
    		return dict(form=form)
      	elif form.errors:
         	response.flash = 'Error'
    	return dict(form=form)

def update_address():
	form=SQLFORM.factory(
		db.Field('query1','string',label='Enter Street'),
		db.Field('query2','string',label='Enter City and Pin'),
		db.Field('query3','string',label='Enter State'))
      	if form.accepts(request.vars, session):
        	db(db.student.student_id==auth.user_id).update(address1=form.vars.query1,address2=form.vars.query2,address3=form.vars.query3)
        	redirect(URL(r=request, f='select_view'))
    		return dict(form=form)
      	elif form.errors:
         	response.flash = 'Error'
    	return dict(form=form)

def mypdf():
    query=(int)(request.args(0))
    r=db((db.student.student_id==query)).select(db.student.ALL)
    s=db((db.course.student_id==query)).select()
    t=db(db.project.student_id==query).select()
    u=db(db.extra.student_id==query).select()
    a=db(db.institution.student_id==query).select()
    b=db(db.work_expr.student_id==query).select()
    c=db(db.activity.student_id==query).select()
    from gluon.contrib.pyfpdf import FPDF, HTMLMixin
    pdf=FPDF()
    pdf.add_page()
    pdf.set_font('Arial','BU',40)
    #pdf.cell(w=60,h=10,txt="",border=2,align='L',fill='0')
    pdf.set_text_color(100,0,100)
    pdf.cell(w=80,h=30,txt="RESUME",ln=2,border=2,align='L',fill='0')
    pdf.set_text_color(0,0,0)
    pdf.set_font('Arial','BU',30)
    pdf.set_text_color(0,0,100)
    pdf.cell(w=80,h=30,txt="My Details:",ln=1,border=2,align='L',fill='0')
    
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="Name  :",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=r[0].name,ln=1,border=2,align='L',fill='0')
    
    str1=str(r[0].age)
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="Age :",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=str1,ln=1,border=2,align='L',fill='0')
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="Gender :",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=r[0].gender,ln=1,border=2,align='L',fill='0')
    
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="Date Of Birth  :",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=str(r[0].dob),ln=1,border=2,align='L',fill='0')
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="Address  :",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=r[0].address1,ln=1,border=2,align='L',fill='0')
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=r[0].address2,ln=1,border=2,align='L',fill='0')
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=r[0].address3,ln=1,border=2,align='L',fill='0')
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="Contact",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=r[0].contact,ln=1,border=2,align='L',fill='0')
    
    pdf.set_font('Arial','',15)
    pdf.set_text_color(0,0,0)
    pdf.cell(w=60,h=10,txt="E-mail :",border=2,align='L',fill='0')
    pdf.cell(w=60,h=10,txt=r[0].email,ln=1,border=2,align='L',fill='0')
    if len(a):
        pdf.set_text_color(0,0,0)
        pdf.set_font('Arial','BU',30)
        pdf.set_text_color(0,0,100)
        pdf.cell(w=80,h=30,txt="EDUCATION",ln=1,border=2,align='L',fill='0')
        for x in a:
            pdf.set_font('Arial','',15)
            pdf.set_text_color(0,0,0)
            #pdf.cell(w=60,h=10,txt=s[0].name :",border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.title,border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.name,ln=1,border=2,align='L',fill='0')
    if len(b):
        pdf.set_text_color(0,0,0)
        pdf.set_font('Arial','BU',30)
        pdf.set_text_color(0,0,100)
        pdf.cell(w=80,h=30,txt="WORK EXPERIENCE",ln=1,border=2,align='L',fill='0')
        pdf.set_font('Arial','',15)
        pdf.set_text_color(0,0,0)
        for x in b:
           
            #pdf.cell(w=60,h=10,txt=s[0].name :",border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.name,border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.as_post,border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.type_of,ln=1,border=2,align='L',fill='0')
    if len(s):
        pdf.set_text_color(0,0,0)
        pdf.set_font('Arial','BU',30)
        pdf.set_text_color(0,0,100)
        pdf.cell(w=80,h=30,txt="COURSES TAKEN",ln=1,border=2,align='L',fill='0')
        for x in s:
            pdf.set_font('Arial','',15)
            pdf.set_text_color(0,0,0)
            #pdf.cell(w=60,h=10,txt=s[0].name :",border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.name,ln=1,border=2,align='L',fill='0')
    if len(t):
        pdf.set_text_color(0,0,0)
        pdf.set_font('Arial','BU',30)
        pdf.set_text_color(0,0,100)
        pdf.cell(w=80,h=30,txt="PROJECTS DONE",ln=1,border=2,align='L',fill='0')
        pdf.set_font('Arial','',15)
        pdf.set_text_color(0,0,0)
        pdf.cell(w=60,h=10,txt="Project Name:",border=2,align='L',fill='0')
        pdf.cell(w=60,h=10,txt="Project Details:",ln=1,border=2,align='L',fill='0')
        for x in t:
            
            #pdf.cell(w=60,h=10,txt=s[0].name :",border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.name,border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.detail,ln=1,border=2,align='L',fill='0')
    if len(u):
        pdf.set_text_color(0,0,0)
        pdf.set_font('Arial','BU',30)
        pdf.set_text_color(0,0,100)
        pdf.cell(w=80,h=30,txt="OTHER ACTIVITIES:",ln=1,border=2,align='L',fill='0')
        pdf.set_font('Arial','',15)
        pdf.set_text_color(0,0,0)
        pdf.cell(w=60,h=10,txt="Name:",border=2,align='L',fill='0')
        pdf.cell(w=60,h=10,txt="Details:",ln=1,border=2,align='L',fill='0')
        for x in u:
            #pdf.cell(w=60,h=10,txt=s[0].name :",border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.title,border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.info,ln=1,border=2,align='L',fill='0')
            
    if len(c):
        pdf.set_text_color(0,0,0)
        pdf.set_font('Arial','BU',30)
        pdf.set_text_color(0,0,100)
        pdf.cell(w=80,h=30,txt="ACHIEVEMENTS",ln=1,border=2,align='L',fill='0')
        pdf.set_font('Arial','',15)
        pdf.set_text_color(0,0,0)
        pdf.cell(w=60,h=10,txt="Name:",border=2,align='L',fill='0')
        pdf.cell(w=60,h=10,txt="Details:",ln=1,border=2,align='L',fill='0')
        for x in c:
            
            #pdf.cell(w=60,h=10,txt=s[0].name :",border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.title,border=2,align='L',fill='0')
            pdf.cell(w=60,h=10,txt=x.detail,ln=1,border=2,align='L',fill='0')

                       
                       
    response.headers['Content-Type']='application/pdf'
    return pdf.output(dest="S")

def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    """
    return dict(form=auth())


def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)


def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()


@auth.requires_signature()
def data():
    """
    http://..../[app]/default/data/tables
    http://..../[app]/default/data/create/[table]
    http://..../[app]/default/data/read/[table]/[id]
    http://..../[app]/default/data/update/[table]/[id]
    http://..../[app]/default/data/delete/[table]/[id]
    http://..../[app]/default/data/select/[table]
    http://..../[app]/default/data/search/[table]
    but URLs must be signed, i.e. linked with
      A('table',_href=URL('data/tables',user_signature=True))
    or with the signed load operator
      LOAD('default','data.load',args='tables',ajax=True,user_signature=True)
    """
    return dict(form=crud())
