class ECRP_TestInteractionAction : ECRP_InteractionAction
{
	void Initialize()
	{
		SetInteractionData(
			"ecrp_test",
			"Test Interaction"
		);
	}

	override void Interact(ECRP_InteractionContext context)
	{
		if (!context)
			return;

		Print(
			"ECRP: Test interaction executed successfully!",
			LogLevel.NORMAL
		);
	}
}