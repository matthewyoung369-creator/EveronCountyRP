[ComponentEditorProps(
	category: "Everon County RP/Interaction",
	description: "Registers and executes a test ECRP interaction"
)]
class ECRP_TestInteractableComponentClass : ScriptComponentClass
{
}

class ECRP_TestInteractableComponent : ScriptComponent
{
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		ECRP_InteractableComponent interactable =
			ECRP_InteractableComponent.Cast(
				owner.FindComponent(ECRP_InteractableComponent)
			);

		if (!interactable)
		{
			Print(
				"ECRP: Test entity is missing ECRP_InteractableComponent.",
				LogLevel.ERROR
			);
			return;
		}

		ref ECRP_TestInteractionAction testAction =
			new ECRP_TestInteractionAction();

		bool registered =
			interactable.RegisterInteractionAction(testAction);

		if (!registered)
		{
			Print(
				"ECRP: Test interaction could not be registered.",
				LogLevel.ERROR
			);
			return;
		}

		Print(
			"ECRP: Test interaction registered.",
			LogLevel.NORMAL
		);

		bool executed = ECRP_InteractionService.TryInteract(
			owner,
			owner,
			"ecrp_test"
		);

		if (!executed)
		{
			Print(
				"ECRP: Test interaction failed to execute.",
				LogLevel.ERROR
			);
		}
	}
}
