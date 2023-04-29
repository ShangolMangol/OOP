package OOP2.Solution;

import OOP2.Provided.ConnectionAlreadyExistException;
import OOP2.Provided.Person;
import OOP2.Provided.SamePersonException;
import OOP2.Provided.Status;

import java.util.*;

public class PersonImpl implements Person {

	private final Integer mId;
	private final String mName;
	private Integer mCurrentStatus;
	private final ArrayList<Person> mFriends;
	private final ArrayList<Status> mStatuses;

	/**
	 * Constructor receiving person's id and name.
	 */
	public PersonImpl(Integer id, String name)
	{
		mId = id;
		mName = name;
		mCurrentStatus = 0;
		mFriends = new ArrayList<>();
		mStatuses = new ArrayList<>();
	}


	@Override
	public Integer getId()
	{
		return mId;
	}

	@Override
	public String getName()
	{
		return mName;
	}

	@Override
	public Status postStatus(String content)
	{
		Status newStatus = new StatusImpl(mCurrentStatus, content, this);
		mCurrentStatus++;
		mStatuses.add(newStatus);
		return newStatus;
	}

	@Override
	public void addFriend(Person p) throws SamePersonException, ConnectionAlreadyExistException
	{
		if(this.equals(p))
			throw new SamePersonException();

		if(mFriends.contains(p))
			throw new ConnectionAlreadyExistException();

		mFriends.add(p);
	}

	@Override
	public Collection<Person> getFriends()
	{
		return mFriends;
	}

	/**
	 * Gets the statuses by given comparator
	 * @param comparator the comparator object to sort by
	 * @return Iterable Status object
	 */
	private Iterable<Status> getStatusesOrdered(Comparator<Status> comparator)
	{
		ArrayList<Status> recentStatuses = new ArrayList<>(mStatuses);
		recentStatuses.sort(comparator);
		return recentStatuses;
	}

	@Override
	public Iterable<Status> getStatusesRecent()
	{
		return getStatusesOrdered(Comparator.comparingInt(Status::getId).reversed());
	}

	@Override
	public Iterable<Status> getStatusesPopular()
	{
		return getStatusesOrdered(Comparator.comparingInt(Status::getLikesCount).reversed());
	}

	@Override
	public int compareTo(Person other)
	{
		return this.mId - other.getId();
	}

	@Override
	public boolean equals(Object obj)
	{
		if(! (obj instanceof Person))
			return false;
		Person other = (Person) obj;
		return Objects.equals(other.getId(), mId);
	}
}
