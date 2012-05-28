import trac.model.ticket as tmt
import web
import markdown

render = None

def updateRender():
    t_globals = {
        'datestr': web.datestr,
        'markdown': markdown.markdown,
        'context': web.ctx.session
    }
    global render
    render = web.template.render(
        'templates/ticket',
        base='base',
        globals=t_globals
    )


def loginRequired(f):
    def _f(*args):
        if web.ctx.session.login:
            updateRender()
            return f(*args)
        else:
            raise web.seeother('/login')
    return _f

class Index:
    @loginRequired
    def GET(self):
        tickets = tmt.get_tickets()
        return render.index(tickets)

class Ticket:
    @loginRequired
    def GET(self, id):
        ticket = tmt.get_ticket_by_id(id)
        if not ticket:
            raise web.seeother('/new?id=%s' % web.websafe(id))
        return render.view(ticket)

class New:
    def not_ticket_exists(url):
        return not bool(tmt.get_ticket_by_url(url))

    ticket_exists_validator = web.form.Validator(
        'Page already exists', not_ticket_exists)

    form = web.form.Form(
        web.form.Textbox('summary', web.form.notnull,
            size=30,
            description="Summary:"),
        web.form.Textbox('reporter', web.form.notnull,
            size=30,
            description="Reporter:"),
        web.form.Textarea('description', web.form.notnull, 
            rows=15, cols=80,
            description="Description:", post="Use <a href='http://en.wikipedia.org/wiki/Markdown'>markdown</a> syntax"),
        web.form.Dropdown('type',
            args = ['task', 'feature', 'defect', 'enhancement'],
            value = 'feature',
            description="Type:"),
        web.form.Dropdown('priority',
            args = ['blocker', 'critical', 'major', 'minor', 'trivial'],
            value = 'major',
            description="Priority:"),
        web.form.Textbox('start', web.form.notnull,
            size=30,
            description="Start(YYYY/MM/DD):"),
        web.form.Textbox('end', web.form.notnull,
            size=30,
            description="End(YYYY/MM/DD):"),
        web.form.Textbox('assignee',
            size=30,
            description="Assign to:"),

        web.form.Button('Create ticket'),
    )

    @loginRequired
    def GET(self):
        url = web.input(url='').url
        form = self.form()
        form.fill({'reporter': web.ctx.session.user.username})
        return render.new(form)

    @loginRequired
    def POST(self):
        form = self.form()
        if not form.validates():
            return render.new(form)
        id = tmt.new_ticket(form.d.summary)
        raise web.seeother('/ticket/%s' % id)

class Delete:
    @loginRequired
    def POST(self, id):
        tmt.del_ticket(int(id))
        raise web.seeother('/ticket')

class Edit:

    form = web.form.Form(
        web.form.Textbox('summary', web.form.notnull,
            size=30,
            description="Summary:"),
        web.form.Button('Update ticket'),
    )

    @loginRequired
    def GET(self, id):
        ticket = tmt.get_ticket_by_id(int(id))
        form = self.form()
        form.fill(ticket)
        return render.edit(ticket, form)


    @loginRequired
    def POST(self, id):
        form = self.form()
        ticket = tmt.get_ticket_by_id(int(id))
        if not form.validates():
            return render.edit(ticket, form)
        tmt.update_ticket(int(id), form.d.summary)
        raise web.seeother('/ticket/%s' % id)

