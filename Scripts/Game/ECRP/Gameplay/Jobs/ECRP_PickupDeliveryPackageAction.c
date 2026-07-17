// Native contextual action exposed by the delivery package's ActionsManagerComponent.
class ECRP_PickupDeliveryPackageAction : ScriptedUserAction
{
	protected static const float MAXIMUM_DISTANCE = 2.0;
	protected static const string DELIVERY_DRIVER_JOB_ID = "delivery_driver";

	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);

		if (!character)
		{
			Print("ECRP: You are not assigned to the Delivery Driver job.", LogLevel.NORMAL);
			return;
		}

		ECRP_PlayerJobComponent jobComponent = ECRP_PlayerJobComponent.Cast(
			character.FindComponent(ECRP_PlayerJobComponent)
		);

		if (!jobComponent || !jobComponent.HasJob(DELIVERY_DRIVER_JOB_ID))
		{
			Print("ECRP: You are not assigned to the Delivery Driver job.", LogLevel.NORMAL);
			return;
		}

		if (!jobComponent.MarkDeliveryPackagePickedUp())
			return;

		Print("ECRP: Delivery package picked up.", LogLevel.NORMAL);
		SCR_EntityHelper.DeleteEntityAndChildren(pOwnerEntity);
	}

	override bool CanBeShownScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool CanBePerformedScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool HasLocalEffectOnlyScript()
	{
		return true;
	}

	override bool GetActionNameScript(out string outName)
	{
		outName = "Pick Up Delivery Package";
		return true;
	}

	protected bool IsUserInRange(IEntity user)
	{
		IEntity owner = GetOwner();

		if (!owner || !user)
			return false;

		return vector.Distance(owner.GetOrigin(), user.GetOrigin()) <= MAXIMUM_DISTANCE;
	}
}
