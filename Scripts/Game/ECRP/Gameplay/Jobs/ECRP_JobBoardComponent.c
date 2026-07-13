[ComponentEditorProps(
	category: "Everon County RP/Jobs",
	description: "Registers job interactions on an ECRP job board"
)]
// Registers the job board as an attachable script component.
class ECRP_JobBoardComponentClass : ScriptComponentClass
{
}

// Adds the delivery driver interaction to an interactable world entity.
class ECRP_JobBoardComponent : ScriptComponent
{
	// Finds the entity's interaction component and registers the job action.
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
				"ECRP: Job board is missing ECRP_InteractableComponent.",
				LogLevel.ERROR
			);
			return;
		}

		ref ECRP_AcceptDeliveryDriverAction action =
			new ECRP_AcceptDeliveryDriverAction();

		action.Initialize();

		if (!interactable.RegisterInteractionAction(action))
		{
			Print(
				"ECRP: Delivery driver interaction could not be registered.",
				LogLevel.ERROR
			);
		}
	}
}
