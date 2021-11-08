#include <iostream>
#include<vector>

using namespace std;

class Card
{
public:
	enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

	Card(rank r , suit s, bool ifu = true) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) { }

	int GetValue() const
	{
		int value = 0;
		if (m_IsFaceUp)
		{
			value = m_Rank;
			if (value > 10)
				value = 10;
		}
		return value;
	}

	void Flip()
	{
		m_IsFaceUp = !m_IsFaceUp;
	}

	friend std::ostream& operator<<(std::ostream& s, const Card& aCard);

private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

class Hand
{
public:
	Hand()
	{
		m_Cards.reserve(7);
	}

	virtual ~Hand()
	{
		Clear();
	}

	void Add(Card* pCard)
	{
		m_Cards.push_back(pCard);
	}

	void Clear()
	{
		std::vector<Card*>::iterator iter = m_Cards.begin();
		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
		{
			delete* iter;
			*iter = nullptr;
		}

		m_Cards.clear();
	}

	int GetTotal() const
	{
		if (m_Cards.empty() || m_Cards[0]->GetValue() == 0)
			return 0;

		int total = 0;
		std::vector<Card*>::const_iterator iter;

		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
			total += (*iter)->GetValue();

		bool containsAce = false;
		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
			if ((*iter)->GetValue() == Card::ACE)
				containsAce = true;

		if (containsAce && total <= 11) total += 10;

		return total;
	}

protected:
	std::vector<Card*> m_Cards;
};

class GenericPlayer : public Hand
{
private:
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
protected:
	string m_name;
public:
	GenericPlayer(const string& name = "") : m_name(name) { }

	virtual ~GenericPlayer();

	virtual bool IsHitting() const = 0;


};

//Task3_OOP6

class Player : public GenericPlayer
{
public:
	Player(const string& name = "") : GenericPlayer(name) { }

	virtual ~Player() { }

	virtual bool IsHitting() const
	{
		cout << m_name << ", do you want a hit? (Y/N): ";
		char response;
		cin >> response;
		return (response == 'y' || response == 'Y');
	}

	void Win() const
	{
		cout << m_name << " win!!!\n";
	}

	void Lose() const
	{
		cout << m_name << " lose :(\n";
	}

	void Push() const
	{
		cout << m_name << " stay.\n";
	}
};

// Task4_OOP6

class House : public GenericPlayer
{
public:
	House(const string& name = "House") : GenericPlayer(name) { }

	virtual ~House() { }

	virtual bool IsHitting() const
	{
		return (GetTotal() <= 16);
	}

	void FlipFirstCard()
	{
		if (!(m_Cards.empty()))
			m_Cards[0]->Flip();
		else
			cout << "Haven`t card to flip\n";
	}
};

int main()
{

}

