void (*tasks[10])(void);
byte nb_tasks = 0;

void add_task(void *fonction)
{
	nb_tasks++;
	tasks[nb_tasks] = &fonction;
}

void delete_task()
{

}

void task()
{
	for()
	{
		try_task:
		tasks[i];
	}
}

void end_task()
{
	goto try_task;
}