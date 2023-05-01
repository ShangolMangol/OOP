package OOP2.Solution;

import OOP2.Provided.*;

import java.util.*;

public class FaceOOPImpl implements FaceOOP
{
	/**
	 * interface for getting a status feed from a person based on some condition
	 */
	private interface FeedCondition
	{
		Iterable<Status> getStatuses(Person person);
	}

	private static final int NOT_REACHABLE = -1;
	private final ArrayList<Person> mUsers;



	/**
	 * Constructor - receives no parameters and initializes the system.
	 */
	public FaceOOPImpl()
	{
		mUsers = new ArrayList<>();
	}

	@Override
	public Person joinFaceOOP(Integer id, String name) throws PersonAlreadyInSystemException
	{
		Person newPerson = new PersonImpl(id, name);
		if(mUsers.contains(newPerson))
			throw new PersonAlreadyInSystemException();

		mUsers.add(newPerson);

		return newPerson;
	}

	@Override
	public int size()
	{
		return mUsers.size();
	}

	@Override
	public Person getUser(Integer id) throws PersonNotInSystemException
	{
		for(Person user : mUsers)
		{
			if(id.equals(user.getId()))
				return user;
		}
		throw new PersonNotInSystemException();
	}

	@Override
	public void addFriendship(Person p1, Person p2) throws PersonNotInSystemException, SamePersonException, ConnectionAlreadyExistException
	{
		if(!(mUsers.contains(p1) && mUsers.contains(p2)))
			throw new PersonNotInSystemException();

		p1.addFriend(p2);
		p2.addFriend(p1);
	}


	/**
	 * gets the person feed based on a given condition for each person status ordered
	 * @param p - the person to gets it's feed
	 * @param condition - the condition interface to extract each friends statuses in the right order
	 * @return iterator to the statuses feed
	 * @throws PersonNotInSystemException if the person doesn't exist in the system
	 */
	public StatusIterator getFeed(Person p, FeedCondition condition) throws PersonNotInSystemException
	{
		if(!mUsers.contains(p))
			throw new PersonNotInSystemException();

		ArrayList<Person> sortedFiends = new ArrayList<>(p.getFriends());
		Collections.sort(sortedFiends);

		//adding each status to the statuses list according to the correct order
		ArrayList<Status> statuses = new ArrayList<>();
		for (Person person : sortedFiends)
		{
			for (Status status : condition.getStatuses(person))
			{
				statuses.add(status);
			}
		}
		return new StatusIteratorImpl(statuses.iterator());
	}

	@Override
	public StatusIterator getFeedByRecent(Person p) throws PersonNotInSystemException
	{
		return getFeed(p, Person::getStatusesRecent);
	}

	@Override
	public StatusIterator getFeedByPopular(Person p) throws PersonNotInSystemException
	{
		return getFeed(p, Person::getStatusesPopular);
	}

	@Override
	public Integer rank(Person source, Person target) throws PersonNotInSystemException, ConnectionDoesNotExistException
	{
		if( !mUsers.contains(source) || !mUsers.contains(target))
			throw new PersonNotInSystemException();

		Map<Person, Integer> ranks = new HashMap<>();
		Set<Person> visited = new HashSet<>();
		Queue<Person> personQueue = new PriorityQueue<>();

		//set all nodes rank
		for (Person p : mUsers)
		{
			if(p.equals(source))
				ranks.put(p, 0);
			else
				ranks.put(p, NOT_REACHABLE);
		}
		//initializing BFS visited and queue
		visited.add(source);
		personQueue.add(source);

		while (!personQueue.isEmpty())
		{
			Person currentNode = personQueue.poll();
			Integer currentRank = ranks.get(currentNode);
			for (Person neighbor : currentNode.getFriends())
			{
				if(visited.contains(neighbor))
					continue;

				visited.add(neighbor);
				ranks.put(neighbor, currentRank + 1);
				personQueue.add(neighbor);
			}
		}

		Integer rank = ranks.get(target);
		if(rank == NOT_REACHABLE)
			throw new ConnectionDoesNotExistException();

		return rank;
	}


	@Override
	public Iterator<Person> iterator()
	{
		ArrayList<Person> sortedUsers = new ArrayList<>(mUsers);
		Collections.sort(sortedUsers);
		return sortedUsers.iterator();
	}

}
