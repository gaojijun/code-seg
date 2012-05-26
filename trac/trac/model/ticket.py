import web
# ticket model

db = web.database(dbn='mysql', db='webpy', user='root')

def get_tickets():
    return db.select('tickets', order='id DESC')

def get_ticket_by_id(id):
    try:
        return db.select('tickets', where='id=$id', vars=locals())[0]
    except IndexError:
        return None

def new_ticket(summary):
    id = db.insert('tickets', summary=summary)
    return id

def del_ticket(id):
    db.delete('tickets', where="id=$id", vars=locals())

def update_ticket(id, summary):
    db.update('tickets', where="id=$id", vars=locals(),
        summary=summary)
