[ComponentEditorProps(
	category: "Everon County RP",
	description: "Stores and manages a player's cash balance"
)]
class ECRP_PlayerMoneyComponentClass : ScriptComponentClass
{
}

class ECRP_PlayerMoneyComponent : ScriptComponent
{
	protected int m_iCash = 2500;

	int GetCash()
	{
		return m_iCash;
	}

	void AddCash(int amount)
	{
		if (amount <= 0)
			return;

		m_iCash += amount;
		PrintFormat("ECRP: Added $%1. New balance: $%2", amount, m_iCash);
	}

	bool RemoveCash(int amount)
	{
		if (amount <= 0)
			return false;

		if (m_iCash < amount)
		{
			PrintFormat("ECRP: Not enough cash. Balance: $%1", m_iCash);
			return false;
		}

		m_iCash -= amount;
		PrintFormat("ECRP: Removed $%1. New balance: $%2", amount, m_iCash);
		return true;
	}

	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		PrintFormat("ECRP: Money component started with $%1", m_iCash);
	}
}